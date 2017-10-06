/*
Client.cpp
Thierry May 2012, May 2013, May 2014
*/

#include "SMC/Client.h"
#include "SMC/SMCProtocol.h"
#include <string.h>

#ifdef WIN32
#include <windows.h> //for Sleep()
#define msleep(A) Sleep(A)
#else
#define msleep(A) usleep((A)*1000.0) 
#endif


using namespace SMC;
using namespace PACC;
using namespace Socket;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : CClient(const char* pServerAddress, const char* pName,       //
//               CProtocol::tSMCModule pSMCModule, double pRepeatTimeout, int //
//               pVerboseLevel)                                               //
//                                                                            //
// DESCRIPTION : Constructor                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

SMC::CClient::CClient(const char* pServerAddress, const char* pName, CProtocol::tSMCModule pSMCModule, double pRepeatTimeout /*=0.0*/, int pVerboseLevel /*=1*/)
   : DirectLink::CClient(pServerAddress, pName)
   , mPeriod(0.0)
   , mLastReception(0.0)
   , mState(stateIDLE)
   , mSMCModule(pSMCModule)
   , mReceptionStatus(rsOkNoNews)
   , mIsNewStatus(false)
   , mIsReportToPush(false)
   , mBackPayloadPtr(NULL)
   , mLastSentBackPayloadPtr(NULL)
   , mLastReceivedStatePtr(NULL)
   , mLastSentBackPayloadTime(0.0)
   , mLastReceivedStateTime(0.0)
   , mRepeatTimeout(pRepeatTimeout)
   , mPayloadSize(0)
   , mBackPayloadSize(0)
   , mVerboseLevel(pVerboseLevel)
{
   if (IsOpen())
      run();
}


CClient::~CClient()
{
   wait(); //wait for thread termination // DO verify

   if (mBackPayloadPtr)
   {
      delete mBackPayloadPtr;
      mBackPayloadPtr = NULL;
      mBackPayloadSize = 0;
   }

   if (mLastSentBackPayloadPtr)
   {
      delete mLastSentBackPayloadPtr;
      mLastSentBackPayloadPtr = NULL;

      mLastSentBackPayloadTime = 0.0;
   }

   if (mLastReceivedStatePtr)
   {
      delete mLastReceivedStatePtr;
      mLastReceivedStatePtr = NULL;
      mPayloadSize = 0;

      mLastReceivedStateTime = 0.0;
   }

   if (mVerboseLevel > 0)
      cout << "SMC Client nicely closed" << endl;
}



//for client site to indicate when READY to handle messages
//we change a state variable for the main loop
int CClient::StartReception()
{
   mSafe.lock();
   mState = stateSTART;
   mSafe.unlock();

   return 0;
}

//for client site to indicate when NOT READY to handle messages
//we change a state variable for the main loop
int CClient::StopReception()
{
   mSafe.lock();
   mState = stateSTOP;

   // Unlock the client loop if waiting and allow it to loop in stateSTOP
   mNewReportToSend.lock();
   mNewReportToSend.broadcast();
   mNewReportToSend.unlock();

   mSafe.unlock();

   return 0;
}

//for client site to indicate FINISH
//we change a state variable for the main loop
int CClient::RequestQuit()
{
   mSafe.lock();

   // Unlock the client loop if waiting and allow it to quit nicely
   mNewReportToSend.lock();
   mNewReportToSend.broadcast();
   mNewReportToSend.unlock();

   mState = stateQUIT;
   mSafe.unlock();

   return 0;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void PushReport(bool pForceIfNotRequired)                    //
//                                                                            //
// PARAMETERS  : pForceIfNotRequired                                          //
//                                                                            //
//                  Force the pushing even if the report is not required      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CClient::PushReport(bool pForceIfNotRequired /*= false*/) 
{ 
   mSafe.lock(); //////////////// Lock

   mIsReportToPush = true;

   //Trig event to stop wating the mandatory report : push report to SMC server
   if (pForceIfNotRequired || mReceptionStatus == rsNewReportRequired)
   {
      mNewReportToSend.lock();
      mNewReportToSend.broadcast();
      mNewReportToSend.unlock();
   }

   mPeriod        = getTime(mLastReception); //update period
   mLastReception = getTime(); //update timestamp

   mSafe.unlock(); /////////// Unlock;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : CClient::ReceptionStatus CheckReceptionStatus()              //
//                                                                            //
// DESCRIPTION : return the reception status: if all is ok (sent box and      //
//               reception box empty, a new report requiring response, a new  //
//               report for info, the last report pushed is not sent yet, or  //
//               if a fail as been received.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

CClient::ReceptionStatus CClient::CheckReceptionStatus() 
{
   if (mState == stateERROR)
   {
      mIsNewStatus = false;
      return rsFail;
   }

   mSafe.lock();

   ReceptionStatus lReceptionStatus = mReceptionStatus;

   if (!mIsNewStatus)
   {
      if (lReceptionStatus == rsNewStateReceived)
         lReceptionStatus = rsOkNoNews; // Old state already read
      else if (lReceptionStatus == rsNewReportRequired)
         lReceptionStatus = rsStillReportRequired; // Old report already read
   }

   mIsNewStatus = false;
   mSafe.unlock();

   return lReceptionStatus;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void main(void)                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CClient::main(void)
{
   //payload size must be obtained by CClient at initialization time

   eState lState = stateIDLE;

   mLastReception = getTime();
   mPeriod = 0.0;

   mReceptionLifoStack.SetBuffersSize( GetPayloadSize() + sizeof(tMsgHeader) );

   ////// Initialize payloadbuffers

   int lLen = 0;

   //create connection with server
   mSafe.lock();
   lState = mState = stateSTART;
   mSafe.unlock();
   sleep(0.1); //to check
   unsigned int lIteration = 0;

   double lInitTime = 0.0;
   lInitTime = getTime();

   //start receiving data in a loop (while)
   while(lState != stateQUIT && lState != stateERROR)
   {	
      //update client side status (whatever the consumer wants)
      mSafe.lock();
      lState = mState;
      mSafe.unlock();

      //manage start/resume, stop/pause, quit from consumer
      switch(lState)
      {
      case stateSTART:
      case stateRUNNING: 
         mSafe.lock();  //// Lock

         { // Locked zone
            /////////////////////////////////////////////////////////////
            ////// Is there a report for the client application to send ?
            /////////////////////////////////////////////////////////////

            if (mState == stateRUNNING && mIsReportToPush)
            { // Let's send last pushed report
               int lDLBackPayloadSize = DirectLink::CClient::GetBackPayloadSize();

               if (mBackPayloadSize > 0)
               {
                  // Check if the new backpayload is different from the last sent
                  //if (memcmp(mLastSentBackPayloadPtr, mBackPayloadPtr, mBackPayloadSize) == 0)
                  if (strncmp(mLastSentBackPayloadPtr, mBackPayloadPtr, mBackPayloadSize) == 0)
                  {
                     double lElapsedTime = getTime(lInitTime) - mLastSentBackPayloadTime;
                     // identical then verify the timeout
                     if (mLastSentBackPayloadTime > 0 && lElapsedTime < mRepeatTimeout) // timeout not expired yet
                     {
                        mIsReportToPush = false;

                        if (mVerboseLevel > 0)
                           cout << "SMC Lib iter " << lIteration << ": Backpayload not sent (already sent" << lElapsedTime << " s ago) to server: \"" << DirectLink::CClient::GetBackPayloadPtr() << "\"." << endl;
                     }
                     else // Repeat (pooling lock) timeout has expired (or is null) then resend the back payload
                     {
                        mLastSentBackPayloadTime = getTime(lInitTime); // Réinit the time stamp

                        if (mVerboseLevel > 0)
                           cout << "SMC Lib iter " << lIteration << ": Backpayload resend (the " << mRepeatTimeout << " s timeout expired) : \"" << DirectLink::CClient::GetBackPayloadPtr() << "\" to server." << endl;
                     }
                  } // End if backpayload not changed
                  else 
                  {  // The last sent payload and the new one are different
                     memcpy(mLastSentBackPayloadPtr, mBackPayloadPtr, mBackPayloadSize); // Update the last payload buffer for next time
                     mLastSentBackPayloadTime = getTime(lInitTime); // Update the time
                  }

                  // If still report to push
                  if (mIsReportToPush)
                  {  // Copy the local back payload (from SMC::Client) to it's base class DirectLink::Client to be send
                     if (mBackPayloadSize >= lDLBackPayloadSize)
                        memcpy(DirectLink::CClient::GetBackPayloadPtr(), mBackPayloadPtr, lDLBackPayloadSize);

                     if (mVerboseLevel > 0)
                        cout << "SMC Lib iter " << lIteration << ": Sending backpayload: \"" << DirectLink::CClient::GetBackPayloadPtr() << "\" to server." << endl;
                  } // End if still report to push

                  // Clear the local (SMC::Client) backpayload for next time
                  memset(mBackPayloadPtr, 0, mBackPayloadSize);
               } // End if backpayload not null
            } // End if mIsReportToPush

            if (mState != stateRUNNING || !mIsReportToPush)
            {  // Echo and empty back payload to the server (no report to push from the client application)
               int lBackPayloadSize = DirectLink::CClient::GetBackPayloadSize();
               if (lBackPayloadSize > 0)
                  memset(DirectLink::CClient::GetBackPayloadPtr(), 0, lBackPayloadSize); // No back payload to return

               if (lState == stateSTART)
               {
                  lState = stateRUNNING;
                  mState = lState;
               }
               else if (mVerboseLevel > 0 && mState == stateRUNNING)
                  cout << "SMC Lib iter " << lIteration << ": Sending echo to server." << endl;
            }

            mIsReportToPush = false; // If needed, report has been copied to backpayload and is ready to be send
         } // End of locked zone

         mSafe.unlock(); //// Unlock

         if (mVerboseLevel > 0)
            cout << "SMC Lib ---> ... SendRequest at T=" << getTime(lInitTime) << " ..." << endl;


         /////////////////////////////////// Envoyer Frame ////////////////
         ////// Send client application response or a simple response
         lLen = SendRequest(cmdNEXT, stateNEW); // Send the first request to start the send & receive loop 
         if (lLen < 0)
         {
            mSafe.lock();
            lState = stateERROR;
            mState = lState;
            mSafe.unlock();

            continue;
         }

         //TODO TM Bug à analyser: le client app doit le reseter jamais ici !!! 
         //mReceptionStatus = rsOkNoNews; // Just sent then no news until next received data bellow

         ////// Wait for a new message (report or state) from SMCServer
         lLen = ReceiveData(mReceptionLifoStack.In());
         if (lLen < 0)
         {
            lState = stateERROR;
            mSafe.lock();
            mState = lState;
            mSafe.unlock();

            continue; // exit loop in stateERROR
         }

         if (mVerboseLevel > 0)
            cout << "SMC Lib <--- ... ReceiveData at T=" << getTime(lInitTime) << endl;

         { // A valid message just received
            const tMsgHeader * lHeader = GetHeaderPtr(mReceptionLifoStack.In());

            if (mVerboseLevel > 0)
               cout << "SMC Lib iter " << ++lIteration << ": " << GetName() << " got ";

            if (lLen == 0)
            {
               if (mVerboseLevel > 0)
                  cout << "a null message!" << endl;

               continue;
            }

            if (mVerboseLevel > 0)
               cout << lHeader->Size << " bytes from " << lHeader->Name << " (Frm=" << lHeader->Frame << ")" << endl;

            mSafe.lock(); //////////////////// Lock
            {
               if (mBackPayloadPtr == NULL)
               {  // Initialization of SMC back payload
                  mBackPayloadSize  = DirectLink::CClient::GetBackPayloadSize(); // Get back paylaod size from the SMC class client
                  mBackPayloadPtr   = new char[mBackPayloadSize];                // Create a local back payload
                  memset(mBackPayloadPtr, 0, mBackPayloadSize);                  // Initialize the back payload with zeros

                  mLastSentBackPayloadPtr = new char[mBackPayloadSize];          // Create another local back payload to keep the last sent
                  memset(mLastSentBackPayloadPtr, 0, mBackPayloadSize);          // Initialize with zeros
               }

               if (mLastReceivedStatePtr == NULL)
               {  // Initialization of the SMC payload (to keep the last receive state)
                  mPayloadSize = DirectLink::CClient::GetPayloadSize(); // Get the payload size
                  mLastReceivedStatePtr = new char[mPayloadSize];       // Create another local back payload to keep the last received state payload
                  memset(mLastReceivedStatePtr, 0, mPayloadSize);       // Initialize with zeros
               }

               mFrame = lHeader->Frame;

               ////////// Is this report for me ? ///////////////
               mIsNewStatus = true;

               mReceptionStatus = rsNewStateReceived;

               if (GetPayloadSize() >= (int)sizeof(CProtocol::tSMCPayload))
               {
                  CProtocol::tSMCPayload * lSMCPayloadPtr = (CProtocol::tSMCPayload *)DirectLink::CClient::GetPayloadPtr(mReceptionLifoStack.In());
                  if (mVerboseLevel > 0)
                  {
                     if (lSMCPayloadPtr->Message[0] == '\0')
                        cout << "SMC Lib iter " << lIteration << ": Received empty payload message" << endl;
                     else
                        cout << "SMC Lib iter " << lIteration << ": Received payload message = " << lSMCPayloadPtr->Message;
                  }

                  if (lSMCPayloadPtr->Dst == mSMCModule)
                  {
                     mReceptionStatus = rsNewReportRequired;
                     if (mVerboseLevel > 0)
                        cout << " for me (answere required)" << endl;
                  }
                  else if (mVerboseLevel > 0)
                     cout << endl;

                  // Check if its a State payload
                  if (lSMCPayloadPtr->Code == 'S')
                  {

                  }

               }

               mReceptionLifoStack.ChangeInIndex(); // Last is now the just received in, and in is now a new free buffer.

               ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
            mSafe.unlock(); /////////////////// Unlock
         }

         ////// Parse the new message

         // If needed, wait the required report to be pushed by the SMC client application (stop the loop in the receive/send side)
         if (mReceptionStatus == rsNewReportRequired)
         {
            // Client application until it push its response report
            mNewReportToSend.lock();
            mNewReportToSend.wait();
            mNewReportToSend.unlock();

            // Client application just done its mandatory push, then let's send info
         }

         break;

      case stateIDLE:
      case stateSTOP:
         //cout << "main sleep" << endl;
         sleep(0.2); //sleep the thread (when no rcv)

         //no need to notify the server (no requests are sent)
         break;

      case stateERROR:
      case stateQUIT:
         //loop shoud exit
         if (mVerboseLevel > 0)
            cout << "quitting..." << endl;
         break;

      default:
         if (mVerboseLevel > 0)
            cout << "unknown state!" << endl;
         break;
      } //case

   } //while
   //finishing loop

   //cout << "main asc quit" << endl;
   //request QUIT
   DirectLink::CClient::RequestQuit();

   return;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : const CProtocol::tSMCPayload * GetPayloadPtr()               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

const CProtocol::tSMCPayload * CClient::GetPayloadPtr()
{
   if (mReceptionLifoStack.ChangeOutIndex() < 0)
      return NULL; // Out buffer not set yet (nothing received yet)

   const char * lBuffer = mReceptionLifoStack.Out().c_str();

   return (const CProtocol::tSMCPayload *) &lBuffer[sizeof(tMsgHeader)];
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
////// Class LifoStack
/////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : LifoStack(int pBuffersSize)                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

LifoStack::LifoStack(int pBuffersSize /*= 0*/)
   : mInIndex(0), mOutIndex(-1), mLastIndex(-1)
{
   if (pBuffersSize > 0)
      SetBuffersSize(pBuffersSize);
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : SetBuffersSize(int pBuffersSize)                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void LifoStack::SetBuffersSize(int pBuffersSize)
{
   for (int i = 0 ; i < 3 ; ++i)
   {
      mStack[i].clear();
      mStack[i].resize(pBuffersSize);
   }
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int ChangeIn()                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int LifoStack::ChangeInIndex()
{
   mIndexMutex.lock();

   mLastIndex = mInIndex; // Last index is now the current in index

   // Look for the next available in index
   for (int i = mInIndex ; i < mInIndex + 3 ; ++i)
   {
      int lNextIndex = (i + 1) % 3;

      if (lNextIndex != mOutIndex)
      {  // Index found
         mInIndex = lNextIndex;
         break;
      }
   }

   mIndexMutex.unlock();

   return mInIndex;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int ChangeOut()                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int LifoStack::ChangeOutIndex()
{
   mIndexMutex.lock();

   if (mOutIndex != mLastIndex)
      mOutIndex = mLastIndex;

   mIndexMutex.unlock();

   return mOutIndex;
}
