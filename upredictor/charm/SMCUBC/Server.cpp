/*
Server.cpp
Denis Ouellet Fev 2012
Thierry Moszkowicz April 2012
*/



#include "SMC/Server.h"
#include "DirectLink/Server.h"


#ifdef WIN32
#include <windows.h> //for Sleep()
#define msleep(A) Sleep(A)
#else
#define msleep(A) usleep((A)*1000.0) 
#endif



#include <iostream>

using namespace SMC;
using namespace PACC;
using namespace std;


CServer::CServer(char *pName, unsigned int pPort, unsigned int pNClients, int pNBuffers, int pPayloadSize, int pBackPayloadSize, int pVerboseLevel /*= 1*/)
   : DirectLink::CServer(pName, pPort, pNClients, pNBuffers, pPayloadSize, pBackPayloadSize, true, pVerboseLevel)
   , mVerboseLevel(pVerboseLevel)
   , mInitTime(getTime())
{
//    AllocateBuffers();
//    mReports.clear();
//    run(pNClients);
}


CServer::~CServer(void)
{
//    wait(); //wait for end
// 
//    //we should do something to close the clients
//    FreeBuffers();
}




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool NewMessageReceived(const tReport & pReport, const       //
//               tMsgHeader* pMsgHeaderPtr)                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CServer::NewMessageReceived(const tReport *pReportPtr)
{
   const tMsgHeader lHeader = pReportPtr->Header;

   if (lHeader.BackPayloadSize == 0)
      return;

   // If backpayload NULL then it's just an echo: nothing more to do
   if (pReportPtr->BackPayload[0] == 0)
   {
      if (mVerboseLevel > 2)
         cout << "New echo message receive " << pReportPtr->SentMsg << " from " << lHeader.Name << endl;

      return; // This is only an echo from client (don't have to push it)
   }

   // Add new backpayload to the list to be analysed in the server application
   LockBackPayloadList();
   mBackPayloadList.push_back(pReportPtr->BackPayload);

   if (mVerboseLevel > 0)
   {
      //cout << "New report received " << pReportPtr->SentMsg << " from " << lHeader.Name << " backpayload size " << lHeader.BackPayloadSize << endl;
      cout << "At " << CServer::getTime(mInitTime) << " New report received " << pReportPtr->SentMsg << " from " << lHeader.Name << ": \"" << pReportPtr->BackPayload << "\"" << endl;;
   }

   //*** SADB ***
   //PublishPayload("SMC.ReportReceived", pReportPtr->BackPayload , lHeader.TimeStamp);
   //le header contient 2 - 3 trucs... src name, ts,  lHeader.Size = hdr+payload //source TS is not copied elsewhere
   
   UnlockBackPayloadList();

    // Trig WaitNextClientReport to indicate to SMCServer application that a new report is in the stack

   mSrvTrigger.lock();
   mSrvTrigger.broadcast();
   mSrvTrigger.unlock();
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool WaitNextClientReport(int pTimeout)                      //
//                                                                            //
// DESCRIPTION : Waits until a client responds or return after a timeout      //
//                                                                            //
// PARAMÈTRES  : pTimeout                                                     //
//                                                                            //
//                  timeout in ms                                             //
//                                                                            //
// RETOUR      : true for a client response, false for a timeout              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool  CServer::WaitNextClientReport(int pTimeout) 
{

   bool lReturn;
   //wait for next reception confirmed
   mSrvTrigger.lock(); 
   lReturn = mSrvTrigger.wait((double)pTimeout / 1000.0); // timeout ms / 1000 = s
   mSrvTrigger.unlock(); 

   return lReturn;
}


//end of Server.cpp
