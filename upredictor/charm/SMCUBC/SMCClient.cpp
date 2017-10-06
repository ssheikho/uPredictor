/*
 * SMCClient.cpp
 * Thierry Moszkowicz, May 2012, May 2013, May 2014
 */


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////// SMC client application example                                  //////
//////                                                                 //////   
////// *************************************************************** //////   
////// ***************** Please: Follow the TODOs ******************** //////
////// *************************************************************** //////   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// TODO: Change this code by yours and keep at least parameters -c, -n and -module to enter the server address, port, the client name, and the module name //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "SMCClient.h"
#include "SMC/Client.h"


#ifdef WIN32
#include <windows.h> //for Sleep()
#define msleep(A) Sleep(A)
#else
#define msleep(A) usleep((A)*1000.0) 
#endif


#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "string.h"

using namespace std;
using namespace SMC;


int main(int argc, char* argv[])
{
   SMCClient lSMCClient;

   // Parameter parsing (return false when help requested or error in parameters)
   if (!lSMCClient.ParseParameters(argc, argv))
      return 0;

   // Loop until return code is different than -2
   // Return code example:
   //    *  0 : Completed without error.
   //    * -1 : Completed with error but quit.
   //    * -2 : Completed with error but loop and try again (typical for connection with server error)

   int lRet;
   do 
   {
      lRet = lSMCClient.main();
   } while (lRet == -2);

   return lRet;
}


SMCClient::~SMCClient()
{
   if (mSMCClientPtr)
   {
      delete mSMCClientPtr;
      mSMCClientPtr = NULL;
   }
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int main()                                                   //
//                                                                            //
// DESCRIPTION : Main program                                                 //
//                                                                            //
// RETURN      : 0 if Ok, -1 if error and stop, -2 if error and restart       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int SMCClient::main()
{
   bool lRunning = true;
   bool lReportToPush = false;

   double lInitTime = 0.0;

   if(!mParams.mIsSMCParamsOk)
      return 0;

   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// TODO: Put first initialization code here if needed
   ////// SMC::CClient not yet created
   ///////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////



   ////////////////////////////////////////////////////////////////


   if(strlen(mParams.mName) == 0)
      strcpy(mParams.mName, "SMCClnt");

   /////////// Don't forget the CProtocol::SMCModule for the module name (T1, T2, ...)
   mSMCClientPtr = new SMC::CClient(mParams.mServerAddress, mParams.mName, mParams.mSMCModule, 5, mParams.mVerboseLevel-1); // First connection try

   int lNbRetry = 0;
   while (mSMCClientPtr && !mSMCClientPtr->IsOpen())
   { // Connection with the SMC server didn't work

      delete mSMCClientPtr;
      mSMCClientPtr = NULL;

      cerr << "SMCClient app error: SMC Client can't create socket to Server! Server may be closed or not ready..." << endl;

      //// Quit if no reconnection requested
      if (mParams.mReconnectionDelay < 0)
      {
         cout << "SMCClient app won't try to reconnect." << endl;
         cout << "Please check server and start program again. Process terminated." << endl;
         return -1;
      } // End if first time


      //// Quit if the maximum retry is reached
      if (lNbRetry++ >= mParams.mReconnectionMaxRetry && mParams.mReconnectionMaxRetry > 0)
      { // Stop client if the maximum retry has been reached
         cout << "SMCClient app: the maximum connection retry (" << mParams.mReconnectionMaxRetry << ") has been reached!" << endl;
         cout << "Please check server and start program again. Process terminated." << endl;
         return -1;
      }

      //// Wait for the requested time
      cout << "SMCClient app waiting " << mParams.mReconnectionDelay << " ms before retry attempt #" << lNbRetry;
      if (mParams.mReconnectionMaxRetry > 0)
         cout << " on " << mParams.mReconnectionMaxRetry << endl;
      else
         cout << " (no maximum) " << endl;

      if (mParams.mReconnectionDelay > 0)
         msleep(mParams.mReconnectionDelay);

      //// Retry to connect
      mSMCClientPtr = new SMC::CClient(mParams.mServerAddress, mParams.mName, mParams.mSMCModule, 5, mParams.mVerboseLevel-1);
   } // End while connection error


   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// TODO: Put second initialization code here if needed
   //////
   ////// SMC::CClient is now connected to server
   ///////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////


   lInitTime = mSMCClientPtr->getTime();
   unsigned int lIteration = 0;

   if (mParams.mVerboseLevel > 0)
      cout << "Client App starting SMC client at T=" << mSMCClientPtr->getTime(lInitTime) << endl;

   mSMCClientPtr->StartReception(); //may be optional?

   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// Main loop starts here
   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////

   CClient::ReceptionStatus lReceptionStatus;
   lRunning = true;
   while(lRunning) 
   {
      // Check the reception status: is all Ok (nothing new), is new State or fail received?, has the last pushed message been sent ?
      lReceptionStatus = mSMCClientPtr->CheckReceptionStatus();
      if (lReceptionStatus == CClient::rsFail)
      {
         //error occured
         cout << "error occured, rsFail received" << endl;
         lRunning = false;
         break;
      }

      // no response to push
      if (lReceptionStatus == CClient::rsOkNoNews)
      {  // No new report
         if (mParams.mVerboseLevel > 2)
            cout << "Client App Iter " << lIteration << ": at T=" << mSMCClientPtr->getTime(lInitTime) << " " << mSMCClientPtr->GetName() << " no news" << endl;
      }
      else
      {
         // New state or report (required or not): rsNewReportRequired, rsNewStateReceived, rsStillReportRequired
         if (mParams.mVerboseLevel > 1)
         {
            if (lReceptionStatus == CClient::rsStillReportRequired)
               cout << "Client App Iter " << lIteration << ": at T=" << mSMCClientPtr->getTime(lInitTime) << " " << mSMCClientPtr->GetName() << " required report still not sent" << endl;
            else
               cout << "Client App Iter " << lIteration << ": at T=" << mSMCClientPtr->getTime(lInitTime) << " " << mSMCClientPtr->GetName() << " got a new report" << endl;
         } // End if new report (required or not)

         ////////////////////////////////////////////////////////////////
         ////////////////////////////////////////////////////////////////
         ////// TODO: Put your code in the following method 
         ////////////////////////////////////////////////////////////////
         lReportToPush = InTheLoopProcess(lReceptionStatus);
         ////////////////////////////////////////////////////////////////
      }

      msleep(mParams.mWait); //mWait is 10ms but this can be used for debug purpose

      if(lIteration >= mParams.mMaxIterations && mParams.mMaxIterations > 0)
      {
         lRunning = false;
         cout << "Reached MaxIterations at " << lIteration << endl;
      }

      if (lReportToPush)
      {
         char * lBackPayloadToPush = mSMCClientPtr->GetBackPayloadPtr();
         if (lBackPayloadToPush) // A first message has already been receive and the backpayload is now initialized
         {
            mSMCClientPtr->PushReport(); ////// Unlock client and send response to server 
            lReportToPush = false;
         }
      }

      lIteration++;
   } // End while running (not stateError)

   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// Main loop ends here
   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////

   if (mParams.mVerboseLevel > 0)
      cout << "Stopping SMC client at " << mSMCClientPtr->getTime(lInitTime) << endl;

   mSMCClientPtr->StopReception();

   if (mParams.mVerboseLevel > 0)
      cout << "quitting..." << endl;
   mSMCClientPtr->RequestQuit();

   // Delete pointer to SMCClient
   delete mSMCClientPtr;
   mSMCClientPtr = NULL;

   //// If connection error, let's retry if requested by parameters
   if (lReceptionStatus == CClient::rsFail)
   {
      if (mParams.mReconnectionDelay > 0)
      {
         cout << endl;
         cout << "******************************************" << endl;
         cout << "*** Program will restart automatically ***" << endl;
         cout << "******************************************" << endl;
         cout << endl;

         return -2; // Will restart the program to try to reconnect
      }

      return -1; // Error, but will not restart
   }


   if (mParams.mVerboseLevel > 0)
      cout << "BYE!" << endl;

   return 0; // Clean termination
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool ParseParameters(int argc, char* * argv)                 //
//                                                                            //
// DESCRIPTION : TODO: Parse application parameters the following method      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::ParseParameters(int argc, char* * argv)
{
   char *lModuleName = NULL;
   mParams.mName[0] = 0;

   for(int i=1; i<argc; i++)
   {
      if(!strcmp(argv[i], "-c"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -c. Address and port number are missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         strcpy(mParams.mServerAddress, argv[i]);
         mParams.mIsSMCParamsOk = true;
         continue;
      } // End if -c


      if(!strcmp(argv[i], "-n"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -n. SMC client name is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         strcpy(mParams.mName, argv[i]);
         continue;
      } // End if -n


      if(!strcmp(argv[i], "-max"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -max. Maximum number of iteration is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         mParams.mMaxIterations = atoi(argv[i]);
         continue;
      } // End if -max


      if(!strcmp(argv[i], "-wait"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -wait. Waiting time value (in ms) is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         mParams.mWait = atoi(argv[i]);

         if (mParams.mWait < 1) 
            mParams.mWait = 10;

         continue;
      } // End if -wait


      if (!strcmp(argv[i], "-timeout"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -timeout. Timeout (in ms) between two identical messages is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         mParams.mRepeatTimeout = (double) atoi(argv[i]) / 1000.0;

         if (mParams.mRepeatTimeout < 0.0)
            mParams.mRepeatTimeout = 0.0;

         continue;
      } // End if -timeout


      if (!strcmp(argv[i], "-autorecon"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -autorecon. Reconnection delay (in ms) is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         mParams.mReconnectionDelay = atoi(argv[i]);

         if (mParams.mReconnectionDelay < 1000)
            mParams.mReconnectionDelay = 1000;

         continue;
      } // End if -autorecon


      if (!strcmp(argv[i], "-maxrecon"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -maxrecon. Maximum number of reconnections is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         mParams.mReconnectionMaxRetry = atoi(argv[i]);

         if (mParams.mReconnectionMaxRetry < 0)
            mParams.mReconnectionMaxRetry = 0;

         continue;
      } // End if -maxrecon


      if(!strcmp(argv[i], "-module"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -module. Module name (code) is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }
         if (lModuleName)
            delete lModuleName;

         lModuleName = new char[strlen(argv[i]) + 1];
         strcpy(lModuleName, argv[i]);

		 cout << "lModule = " << lModuleName << endl;

		 mParams.mSMCModule = CProtocol::GetModuleId(lModuleName);

		 cout << "lModuleId = " << (int)mParams.mSMCModule << endl;

		 continue;
      } // End if -module


      if(!strcmp(argv[i], "-verbose"))
      {
         if (++i >= argc)
         {
            cerr << "SMCClient app: Invalid parameter -autorecon. Auto reconnection delay (in ms) is missing." << endl;
            mParams.mIsSMCParamsOk = false;
            break;
         }

         mParams.mVerboseLevel = atoi(argv[i]);
         continue;
      }
   } // End if -verbose


   // Take module name by default
   if (mParams.mName[0] == 0 && lModuleName != NULL && lModuleName[0] != 0)
      strcpy(mParams.mName, lModuleName); 

   if (mParams.mVerboseLevel > 0)
   {
      cout << "Verbose Level = " << mParams.mVerboseLevel << endl;
      cout << "Name = \"" << mParams.mName << "\"" << endl;

      if (mParams.mIsSMCParamsOk)
      {
         cout << "<IP or Hostname>:PortNum = \"" << mParams.mServerAddress << "\"" << endl;
      }

      cout << "Pooling lock timeout = " << mParams.mRepeatTimeout << " s" << endl;

      if (mParams.mMaxIterations > 0)
         cout << "lMaxIterations = " << mParams.mMaxIterations << endl;

      cout << "lWait = " << mParams.mWait << endl;

      if (mParams.mReconnectionDelay > 0)
      {
         cout << "Auto reconnection activated:" << endl;
         cout << "    reconnection delay: " << mParams.mReconnectionDelay / 1000.0 << " s" << endl;
         if (mParams.mReconnectionMaxRetry > 0)
            cout << "    maximum reconnection number: " << mParams.mReconnectionMaxRetry << "." << endl;
      } // End if autorecon
   } // End if verbose

   if (!mParams.mIsSMCParamsOk)
      PrintParametersHelp(argv[0]);

   return mParams.mIsSMCParamsOk;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcess(CClient::ReceptionStatus               //
//               pReceptionStatus)                                            //
//                                                                            //
// DESCRIPTION : SMCClient must do its work here in the reception loop        //
//                                                                            //
// RETURN      : True to push a new report (required for the state            //
//               rsNewReportRequired), false if you don't have to push a new  //
//               report (or if you can't push the required report yet         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcess(CClient::ReceptionStatus pReceptionStatus)
{
   ///////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////
   ////////////////// TODO: Put your in the main loop code here
   ///////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////

   const CProtocol::tSMCPayload * lPayloadPtr = mSMCClientPtr->GetPayloadPtr();
   if (lPayloadPtr == NULL)
      return false; // This case must not arrived here, but please take care to check the validity of this pointer if you call GetPayloadPtr() somewhere else. (NULL when no payload has never been receive yet)

   if (mParams.mVerboseLevel > 0)
   {
      if (lPayloadPtr->Message[0] != '\0')
         cout << "Client App payload = " << lPayloadPtr->Message;
      else
         cout << "Client App empty payload (echo)" << endl;
   }

   ////// The client has a report to push (some clients may not whant to push a report if a new state is received)
   ////// Remark: a report is new and required or still required when the message (in the payload) if for it
   //////         all other clients (not in the dest received the same message as a new state.
   if (  pReceptionStatus == CClient::rsNewReportRequired   // The new message is explicitly for me
      || pReceptionStatus == CClient::rsStillReportRequired // The previouly received message is (was) explictly for me
      || pReceptionStatus == CClient::rsNewStateReceived  ) // The message is for ALL or another client, but some client I may whant the send a report in this case too
   {
      char *lBackPayloadPtr   = mSMCClientPtr->GetBackPayloadPtr();
      int lBackPayloadSize    = mSMCClientPtr->GetBackPayloadSize();


      ////////////////////////////////////////////////////////////////////////////
      ////// TODO: Write your report message int the back payload here
      ////////////////////////////////////////////////////////////////////////////
      // For instance, here is a sample message from T1 (T1Done or T1Read): Replace this line by yours

/*
      switch (lPayloadPtr->State)
      {
	
      case CProtocol::InitT1:
         strncpy(lBackPayloadPtr, "T1  SMC R T1Ready", lBackPayloadSize); // This is an example for module T1
         break;

      case CProtocol::T1DeliverPart:
         {
            static bool lblIsCondition1 = true;
            if (lblIsCondition1)
               strncpy(lBackPayloadPtr, "T1 SMC R T1Done", lBackPayloadSize); // This is an example for module T1
            else
               strncpy(lBackPayloadPtr, "T1 SMC R PartTaken", lBackPayloadSize); // This is an example for module T1

            lblIsCondition1 = ! lblIsCondition1;

            break;
         }

      case CProtocol::FinishT1:
         strncpy(lBackPayloadPtr, "T1 SMC R T1Done", lBackPayloadSize); // This is an example for module T1
         break;

      case CProtocol::T1RetractTray:
         strncpy(lBackPayloadPtr, "T1 SMC R TrayRetracted", lBackPayloadSize); // This is an example for module T1
         break;

      default:
         return false;
      } // End switch payload state
*/

      lBackPayloadPtr[lBackPayloadSize-1]= '\0'; // Protection just in case the string is (by error) bigger than the allowed back payload size

      ////////////////////////////////////////////////////////////////////////////

      return true; // Must return true when a new report is required to unlock the SMC reception loop
   }

   return false;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void PrintParametersHelp()                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void SMCClient::PrintParametersHelp(const char * pAppName)
{
   cout << endl << "---------------" << endl;
   cout << "Error: use " << pAppName << " -c <host ip address>:<port number> [Options]" << endl << endl;
   cout << "Options: " << endl;
   cout << "   -n client name" << endl;
   cout << "   -module <SMCModule name> (T1, T2, T3, T3P, T3W or T3O)" << endl;
   cout << "   -wait ms (For server only. Default=10)" << endl;
   cout << "   -timeout ms (Repeat timeout. Default=2000)" << endl;
   cout << "   -max <MaxIterations>" << endl;
   cout << "   -autorecon ms <delay> (min 1000 for a 1s delay). Auto reconnection delay. (Default don't retry to reconnect automatically)" << endl;
   cout << "   -maxrecon <# of retry> (Default=0 for infinit loop when the -autoreconnect parameter is present)" << endl;
   cout << "   -verbose <verbose level> (0 for mute, 1 a little, ... Default = 1)";
   cout << endl << endl;
   cout << "Example: " << endl;
   cout << "   " << pAppName << " -c 127.0.0.1:1234 -n ClientT1 -module T1 -autorecon 1000 -maxrecon 60" << endl;
   cout << "---------------" << endl << endl;
}
