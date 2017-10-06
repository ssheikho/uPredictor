/*
 * SMCClientSim.cpp
 * Denis Ouellet, May 2012
 * Modified by:
 *    TM, May 2013, May 2014
 *
 *using 
 *SMCClient.cpp as original model (released 2012-05-15)
 * Thierry Moszkowicz, May 2012, May 2013
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// TODO: Change this code by yours and keep at least parameters -c, -n and -module to enter the server address, port, the client name, and the module name //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "SMCClientSim.h"
#include "SMC/Client.h"


#ifdef WIN32
#include <windows.h> //for Sleep()
#define msleep(A) Sleep(A)
#else
#define msleep(A) usleep((A)*1000.0) 
#endif

#ifdef WIN32
#define UNUSED
#else
#define UNUSED  __attribute__((unused))
#endif

#define SUPPLY_CYCLES 2


#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "string.h"

using namespace std;
using namespace SMC;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// FUNCTION    : int main(int argc, char* argv[])                             //
//                                                                            //
// DESCRIPTION : Application entry point                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : Params()                                                     //
//                                                                            //
// DESCRIPTION : Constructeur                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

SMCClient::Params::Params()
   : mMaxIterations(0)        // 0 for endless loop by default
   , mWait(10)                // Wait 10ms in the loop (between two messages) by default
   , mReconnectionDelay(-1)   // No reconnection by default
   , mReconnectionMaxRetry(0) // Endless trying loop by default (if the timeout is positive)
   , mIsSMCParamsOk(false)
   , mVerboseLevel(1)
{
   for (int i=0 ; i<NAME_SIZE ; ++i)
      mName[i] = '\0';

   //flags to enable simulation
   for(int i=0; i<SMC::CProtocol::NbSMCModules; i++)
      mSimModule[i] = false;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : SMCClient()                                                  //
//                                                                            //
// DESCRIPTION : Constructeur                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

SMCClient::SMCClient()
{
   for(int i=0; i<CProtocol::NbSMCModules; i++)
   {
      mSMCClientPtr[i] = NULL;
   }
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : ~SMCClient()                                                 //
//                                                                            //
// DESCRIPTION : Destructeur                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

SMCClient::~SMCClient()
{
   for(int i=0; i<CProtocol::NbSMCModules; i++)
   {
      if (mSMCClientPtr[i])
      {
         delete mSMCClientPtr[i];
         mSMCClientPtr[i] = NULL;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int main()                                                   //
//                                                                            //
// DESCRIPTION : Main program                                                 //
//                                                                            //
// RETOUR      : 0 if Ok, -1 if error and stop, -2 if error and restart       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int SMCClient::main()
{
   bool lRunning = true;
   bool lReportToPush = false;

   double lInitTime = 0.0;

   static const char* lNames[CProtocol::NbSMCModules]; 

   for(int lModId=0; lModId<CProtocol::NbSMCModules; lModId++)
	   lNames[lModId] = CProtocol::GetModuleName(lModId);

   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// TODO: Parse application parameters the following method
   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////

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

   //// Start all requested clients (enabled modules)
   for(int iClient=0 ; iClient < CProtocol::NbSMCModules ; iClient++)
   {
      if(!mParams.mSimModule[iClient]) //enabled module
         continue;

      int lNbRetry = 0;

      mSMCClientPtr[iClient] = new SMC::CClient(mParams.mServerAddress, lNames[iClient], (CProtocol::tSMCModule)iClient, 2.0, mParams.mVerboseLevel - 1);
      while (mSMCClientPtr[iClient]  && !mSMCClientPtr[iClient]->IsOpen())
      {  
		  /////  // Connection with the SMC server didn't work
         //// Delete all clients already created (it's probably the first one, but we never kwnow!)
         for (int iDelete = 0 ; iDelete <= iClient ; iDelete++)
         {
            if (!mSMCClientPtr[iDelete])
               continue;

            delete mSMCClientPtr[iDelete];
            mSMCClientPtr[iDelete] = NULL;
         }

         cerr << "SMCClientSim: error: SMC Client \"" << lNames[iClient] << "\" (#" << iClient + 1 << ") can't create socket to Server! SMC server may be closed or not ready..." << endl;

         //// Quit if no reconnection requested
         if (lNbRetry++ == 0 && mParams.mReconnectionDelay < 0)
         {
            cout << "SMCClientSim: won't try to reconnect." << endl;
            cout << "Please check server and start program again. Process terminated." << endl;
            return -1;
         } // End if first time


         //// Quit if the maximum retry is reached
         if (mParams.mReconnectionMaxRetry > 0 && lNbRetry > mParams.mReconnectionMaxRetry)
         { // Stop server if the maximum retry has been reached
            cout << "SMCClientSim: the maximum connection retry (" << mParams.mReconnectionMaxRetry << ") has been reached!" << endl;
            cout << "Please check server and start program again. Process terminated." << endl;
            return -1;
         }


         //// Reinit index to the first client (enabled module) and try again if requested by parameters
         for(iClient=0 ; iClient < CProtocol::NbSMCModules ; iClient++)
         {
            if(mParams.mSimModule[iClient]) //enabled module
               break;
         }

         //// Wait for the requested time
         cout << "SMCClientSim: waiting " << mParams.mReconnectionDelay << "ms before retry attempt #" << lNbRetry;
         if (mParams.mReconnectionMaxRetry > 0)
            cout << " on " << mParams.mReconnectionMaxRetry << endl;
         else
            cout << " (no maximum) " << endl;

         if (mParams.mReconnectionDelay > 0)
            msleep(mParams.mReconnectionDelay);

         //// Retry to connect
         mSMCClientPtr[iClient] = new SMC::CClient(mParams.mServerAddress, lNames[iClient], (CProtocol::tSMCModule)iClient, 2.0, mParams.mVerboseLevel - 1);
      } // End while not isOpen

      //// Client is now connected to the SMC server
      lInitTime = mSMCClientPtr[iClient]->getTime();

      cout << "SMCClientSim: Starting client " << iClient << " at T=" << mSMCClientPtr[iClient]->getTime(lInitTime) << endl;
      mSMCClientPtr[iClient]->StartReception(); //may be optional?
   } // End for iClient


   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// TODO: Put second initialization code here if needed
   ////// SMC::CClient si now connected to server
   ///////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////

      
   unsigned int lIteration = 0;

   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// Main loop starts here
   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////

   //// Loop for all clients
   CClient::ReceptionStatus lReceptionStatus;
   lRunning = true;
   while (lRunning) 
   {
      for (int iModule = 0 ; iModule < CProtocol::NbSMCModules ; iModule++)
      {
         if (mSMCClientPtr[iModule] == NULL) 
            continue; // This module has not been enabled

         // Check the reception status: is all Ok (nothing new), 
         //is new State or fail received?, 
         //has the last pushed message been sent ?
         lReceptionStatus = mSMCClientPtr[iModule]->CheckReceptionStatus();
         if (lReceptionStatus == CClient::rsFail)
         {  // An error occurred: server has probably been closed
            lRunning = false; // Quit the main loop
            break;
         }
         
         if (lReceptionStatus != CClient::rsOkNoNews)
            lReportToPush = InTheLoopProcess(lReceptionStatus, (CProtocol::tSMCModule)iModule);

         if (lReportToPush)
         {
            char* lReportStr = mSMCClientPtr[iModule]->GetBackPayloadPtr();
            if (lReportStr) // A first message has already been receive and the BackPayload is now initialized
            {
               ////// Write data to the backPayload to push
               mSMCClientPtr[iModule]->PushReport(); ////// Unlock client and send response to server 
               lReportToPush = false;
            }
         } //if report
      } //for modules
   

      /*
      if(lIteration >= mParams.mMaxIterations && mParams.mMaxIterations > 0)
      {
         lRunning = false;
         cout << "Reached MaxIterations at " << lIteration << endl;
      }*/

      msleep(mParams.mWait); //mWait is 0ms but this can be used for debug purpose

      lIteration++;
   } // End while running (not stateError)

   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////
   ////// Main loop ends here
   ////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////

   cout << "SMCClientSim: Stopping all clients:" << endl;
   for (int iClient = 0 ; iClient < CProtocol::NbSMCModules ; iClient++)
   {
      if(mSMCClientPtr[iClient] == NULL) 
         continue;

      if (mSMCClientPtr[iClient]->IsOpen()) // The client may be already closed if server already closed
      {
         cout << "SMCClientSim: Stopping SMC client \"" << lNames[iClient] << "\" (#" << iClient + 1 << ") at " << mSMCClientPtr[iClient]->getTime(lInitTime) << endl;

         mSMCClientPtr[iClient]->StopReception();

         cout << "SMCClientSim: Quitting SMC client ..." << endl;
         mSMCClientPtr[iClient]->RequestQuit();
      }
      else
      {
         cout << "SMCClientSim: SMC client \"" << lNames[iClient] << "\" (#" << iClient + 1 << ") already closed at " << mSMCClientPtr[iClient]->getTime(lInitTime) << endl;
      }
   }

   //// If connection error, let's retry if requested by parameters
   if (lReceptionStatus == CClient::rsFail && mParams.mReconnectionDelay > 0)
   {
      cout << endl;
      cout << "******************************************" << endl;
      cout << "*** Program will restart automatically ***" << endl;
      cout << "******************************************" << endl;
      cout << endl;
      return -2; // Will restart the program to try to reconnect
   }

   cout << "SMCClientSim: BYE!" << endl;

   // Delete clients
   for(int i=0; i<CProtocol::NbSMCModules; i++)
   {
      if (mSMCClientPtr[i])
      {
         delete mSMCClientPtr[i];
         mSMCClientPtr[i] = NULL;
      }
   }

   cout << "SMCClient terminated." << endl;

   return 0;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool ParseParameters(int argc, char* * argv)                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::ParseParameters(int argc, char* * argv)
{
   bool lMinOneModule = false;

   for(int i=1; i<argc; i++)
   {
      if(!strcmp(argv[i], "-c") || !strcmp(argv[i], "-ac"))
      {
         cout << "client operation" << endl;
         strcpy(mParams.mServerAddress, argv[i+1]);
         i++;
         cout << "<IP or Hostname>:Port = \"" << mParams.mServerAddress << "\"" << endl;
         mParams.mIsSMCParamsOk = true;
      }

      /*
      if(!strcmp(argv[i], "-n"))
      {
         strcpy(mParams.mName, argv[i+1]);
         cout << "lName = " << mParams.mName << endl;
         i++;
      }

      if(!strcmp(argv[i], "-max"))
      {
         cout << "max iterations" << endl;
         mParams.mMaxIterations = atoi(argv[i+1]);
         cout << "lMaxIterations = " << mParams.mMaxIterations << endl;
         i++;
      }

      if(!strcmp(argv[i], "-wait"))
      {
         mParams.mWait = atoi(argv[i+1]);
         cout << "lWait = " << mParams.mWait << endl;
         i++;

         if (mParams.mWait < 1) 
            mParams.mWait = 20;
      }
      */

      if (!strcmp(argv[i], "-autorecon"))
      {
         mParams.mReconnectionDelay = atoi(argv[i+1]);
         i++;

         if (mParams.mReconnectionDelay < 1000)
            mParams.mReconnectionDelay = 1000;
      }

      if (!strcmp(argv[i], "-maxrecon"))
      {
         mParams.mReconnectionMaxRetry = atoi(argv[i+1]);
         i++;

         if (mParams.mReconnectionMaxRetry < 0)
            mParams.mReconnectionMaxRetry = 0;
      }

      /*
      if(!strcmp(argv[i], "-module"))
      {
         char lModule[CProtocol::MaxConditionLen+1];
         strncpy(lModule, argv[i+1], CProtocol::MaxModuleNameLen);
         lModule[CProtocol::MaxModuleNameLen] = '\0';

         cout << "lModule = " << lModule << endl;
         i++;

         if (!strcmp(lModule, "T1"))
            pParams.mSMCModule = CProtocol::T1;
         else if (!strcmp(lModule, "T2"))
            pParams.mSMCModule = CProtocol::T2;
         else if (!strcmp(lModule, "T3"))
            pParams.mSMCModule = CProtocol::T3;
         else if (!strcmp(lModule, "T3P"))
            pParams.mSMCModule = CProtocol::T3P;
         else if (!strcmp(lModule, "T3W"))
            pParams.mSMCModule = CProtocol::T3W;
         else if (!strcmp(lModule, "T3O"))
            pParams.mSMCModule = CProtocol::T3O;
         else
            pParams.mSMCModule = CProtocol::UNKNOWN;
      }
      */


      //flags for simulation modes (all of them can be set to true)
      //simulated modules will actually replace and respond in place of missing modules
      //with expected behavior (sending the correct reports to make SMC sequencing happy)

	  /*
	  if(!strcmp(argv[i], "-SMC"))
	  {
		  cout << "Sim SMC" << endl;
		  mParams.mSimModule[CProtocol::SMC] =true; 
		  lMinOneModule = true;
	  }
	  */

	  if(!strcmp(argv[i], "-SADB"))
	  {
		  cout << "Sim SADB" << endl;
		  mParams.mSimModule[CProtocol::SADB] =true; 
		  lMinOneModule = true;
	  }

	  if(!strcmp(argv[i], "-T1"))
      {
         cout << "Sim T1" << endl;
         mParams.mSimModule[CProtocol::T1] =true; 
         lMinOneModule = true;
      }

      if(!strcmp(argv[i], "-T2"))
      {
         cout << "Sim T2" << endl;
         mParams.mSimModule[CProtocol::T2] =true;
         lMinOneModule = true;
      }

	  if(!strcmp(argv[i], "-IAD"))
	  {
		  cout << "Sim IAD" << endl;
		  mParams.mSimModule[CProtocol::IAD] =true;
		  lMinOneModule = true;
	  }

	  if(!strcmp(argv[i], "-KUKA"))
	  {
		  cout << "Sim KUKA" << endl;
		  mParams.mSimModule[CProtocol::KUKA] =true;
		  lMinOneModule = true;
	  }

	  if(!strcmp(argv[i], "-T2"))
	  {
		  cout << "Sim T2" << endl;
		  mParams.mSimModule[CProtocol::T2] =true;
		  lMinOneModule = true;
	  }

	  if(!strcmp(argv[i], "-GRIP"))
	  {
		  cout << "Sim GRIP" << endl;
		  mParams.mSimModule[CProtocol::GRIP] =true;
		  lMinOneModule = true;
	  }

	  if(!strcmp(argv[i], "-T3K"))
	  {
		  cout << "Sim T3K" << endl;
		  mParams.mSimModule[CProtocol::T3K] =true;
		  lMinOneModule = true;
	  }

      if(!strcmp(argv[i], "-T3O"))
      {
         cout << "Sim T3O" << endl;
         mParams.mSimModule[CProtocol::T3O] =true;
         lMinOneModule = true;
      }

      if(!strcmp(argv[i], "-T3P"))
      {
         cout << "Sim T3P" << endl;
         mParams.mSimModule[CProtocol::T3P] =true;
         lMinOneModule = true;
      }

      if(!strcmp(argv[i], "-T3W"))
      {
         cout << "Sim T3W" << endl;
         mParams.mSimModule[CProtocol::T3W] =true;
         lMinOneModule = true;
      }

      if(!strcmp(argv[i], "-verbose"))
      {
         mParams.mVerboseLevel = atoi(argv[i+1]);
         i++;

         //if (pParams.mTimeout < 1) 
         //   pParams.mTimeout = 20;
      }
   }

   if(!lMinOneModule)
   {
      mParams.mSimModule[CProtocol::UNKNOWN] = true; //enable unknown when no module is specified
      cout << "enabling default UNKNOWN module" << endl;
      lMinOneModule = true;
   }

   //ore or more module is required
   if(!lMinOneModule)
      mParams.mIsSMCParamsOk = false;

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

bool SMCClient::InTheLoopProcess(CClient::ReceptionStatus pReceptionStatus, const CProtocol::tSMCModule &pModule)
{

   /*
   switch (pReceptionStatus)
   { 
   case CClient::rsOkNoNews: // Nothing new, reception and sent boxes empty
      // no response to push
      break;

   case CClient::rsNewReportRequired:
   case CClient::rsNewStateReceived:
      //reporting
      cout << "Client#" << i << " Iter " << lIteration << ": at T=" << mSMCClientPtr[i]->getTime(lInitTime) << " " << mSMCClientPtr[i]->GetName() << " got a new report" << endl;

      ////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////
      ////// TODO: Put your code in the following method 
      ////////////////////////////////////////////////////////////////

      ////////////////////////////////////////////////////////////////

      break;

   case CClient::rsFail:
      //error occurred
      cout << "error occurred, rsFail received" << endl;
      lRunning = false;
      break;
   } // End switch ReceptionStatus

   */


   bool  lReturn = false;
   char *lReportStr  = mSMCClientPtr[pModule]->GetBackPayloadPtr();
   int   lReportSize = mSMCClientPtr[pModule]->GetBackPayloadSize();

   const CProtocol::tSMCPayload * lPayloadPtr = mSMCClientPtr[pModule]->GetPayloadPtr();
   if (lPayloadPtr == NULL)
   {  
      //cout << "Error: no payload!" << endl;
      lReturn = false; // This case must not arrive here, but please take care to check the validity of this pointer if you call GetPayloadPtr() somewhere else. (NULL when no payload has never been receive yet)
      goto completed;
   }

   /*  //this one prevents module to know current state (not in message)
   if(lPayloadPtr->Message[0]=='\0')
   {
      lReturn = false; //empty message, should be taken care of at higher level
      goto completed;
   }
   */
   
   //dispatch to sub-module
   switch(pModule)
   {
/*
   case CProtocol::SMC:
	   lReturn = InTheLoopProcessSMC(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
	   break;
*/

   case CProtocol::SADB:
	   lReturn = InTheLoopProcessSADB(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
	   break;

/*
   case CProtocol::T1:
      lReturn = InTheLoopProcessT1(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
      break;

   case CProtocol::T2:
      lReturn = InTheLoopProcessT2(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
      break;
*/

   case CProtocol::IAD:
	   lReturn = InTheLoopProcessIAD(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
	   break;

   case CProtocol::KUKA:
	   lReturn = InTheLoopProcessKUKA(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
	   break;

   case CProtocol::GRIP:
	   lReturn = InTheLoopProcessGRIP(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
	   break;

   case CProtocol::T3K:
	   lReturn = InTheLoopProcessT3K(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
	   break;

   case CProtocol::T3P:
      lReturn = InTheLoopProcessT3P(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
      break;

   case CProtocol::T3W:
      lReturn = InTheLoopProcessT3W(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
      break;


   case CProtocol::T3O:
      lReturn = InTheLoopProcessT3O(pReceptionStatus, lReportStr, lReportSize, lPayloadPtr);
      break;

   
   default:
      lReturn = false;
      break;
   }

   if(lReturn)
      cout << "SMCClientSim: REPORT " << lReportStr << endl;

completed:
   return lReturn;  // Must return true when a new report is required to unlock the SMC reception loop
}


#ifdef __TOTO_NO_SMC__
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessSMC(SMC::CClient::ReceptionStatus        //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessSMC(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
	bool  lReturn = false;

	static int lLocalState = 0; 

	//if (pReceptionStatus == CClient::rsNewReportRequired)

	//BUG: everyone sends stuff to SMC... SMC Cleint must then respond to all messages
	//BAD idea to have a SMC client...

	if (pReceptionStatus == CClient::rsNewReportRequired)
	{
		//just send SMCREady if necessary
		if(pPayloadPtr->Conditions[CProtocol::SMCReady]==CProtocol::eFALSE)
			strncpy(pReportStr, "SMC ALL R SMCReady", pReportSize);
		else
			strncpy(pReportStr, "", pReportSize);

		lReturn = true;
	}
	else
	if(true) //pPayloadPtr->Src!=CProtocol::SMC)
	{
		switch(pPayloadPtr->State)
		{ 
		case CProtocol::Begin:
		case CProtocol::Initialization:
		case CProtocol::InitTaskInfo:
			//if(pPayloadPtr->Conditions[CProtocol::SMCReady])
			//	break;
			if (pReceptionStatus != CClient::rsNewReportRequired)
				break;

			strncpy(pReportStr, "SMC ALL R SMCReady", pReportSize);
			lLocalState = 1;
			lReturn = true;
			break;
		
		case CProtocol::STATE_UNKNOWN:
		default:
			lLocalState = 0;
			lReturn = false;
		}
	}

	return lReturn; 
}
#endif

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessSADB(SMC::CClient::ReceptionStatus        //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessSADB(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
	bool  lReturn = false;

	if (pReceptionStatus == CClient::rsNewReportRequired)
	{
		if(pPayloadPtr->Conditions[CProtocol::SADBReady])
			strncpy(pReportStr, "SADB SMC R SADBReady", pReportSize);
		else
			strncpy(pReportStr, "", pReportSize);
	
		lReturn = true;
	}

	if(pPayloadPtr->Src!=CProtocol::SADB)
	{
		switch(pPayloadPtr->State)
		{
			/*
		case CProtocol::InitSADB:
		case CProtocol::FinishSADB:
			strncpy(pReportStr, "SADB SMC R SADBReady", pReportSize);
			lLocalState = 1;
			lReturn = true;
			break;
			*/

		case CProtocol::Begin:
		case CProtocol::Initialization:
		case CProtocol::InitTaskInfo:

			if(pPayloadPtr->Conditions[CProtocol::SADBReady])
				break;

			strncpy(pReportStr, "SADB SMC R SADBReady", pReportSize);
			lReturn = true;
			break;


		case CProtocol::LoadScript:
			strncpy(pReportStr, "SADB SMC R SADBReady", pReportSize);
			lReturn = true;
			break;

		case CProtocol::Finish:
			strncpy(pReportStr, "SADB SMC R SADBReady", pReportSize);
			lReturn = true;


		case CProtocol::STATE_UNKNOWN:
		default:
			//lReturn = false;
			break;
		}
	}

	return lReturn; 
}

#ifdef __NO_T1__
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT1(SMC::CClient::ReceptionStatus        //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessT1(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   static int lLocalState = 0; 

   //if (pReceptionStatus == CClient::rsNewReportRequired)
   if(pPayloadPtr->Src!=CProtocol::T1)
   {
      switch(pPayloadPtr->State)
      {
      case CProtocol::InitT1:
         strncpy(pReportStr, "T1 SMC R T1Ready", pReportSize);
         lLocalState = 1;
         lReturn = true;
         break;

      case CProtocol::T1DeliverPart:

         //we have many more reports available... I need to put these to trigger responses from T3 algorithms
         //we should look into SMCPayload to know where we are
         //TODO: DO lPayloadPtr->Conditions[]==eTRUE;

         if(pPayloadPtr->Conditions[CProtocol::PresentingPart] == CProtocol::eFALSE && lLocalState < 3)
         {
            strncpy(pReportStr, "T1 SMC R PresentingPart", pReportSize);
            lLocalState = 3;
            lReturn = true;
         }
         else
         if(pPayloadPtr->Conditions[CProtocol::PresentingPart] == CProtocol::eTRUE && lLocalState < 8)
         {
            strncpy(pReportStr, "T1 SMC R T1Done", pReportSize);
            lLocalState = 8;
            lReturn = true;
         }

         //this one is not handled by T1 (it is part of AssemblyComplete and NextPart from T3P)
         //if(pPayloadPtr->Conditions[CProtocol::PartInPlace] == CProtocol::eTRUE)
         
         break;

      case CProtocol::T1RetractTray:

            if(pPayloadPtr->Conditions[CProtocol::TrayRetracted] == CProtocol::eFALSE && lLocalState < 9)
            {
               strncpy(pReportStr, "T1 SMC R TrayRetracted", pReportSize);
               lLocalState = 9;
               lReturn = true;
            }
         break;


      case CProtocol::FinishT1:
         if(lLocalState != 1)
         {
            strncpy(pReportStr, "T1 SMC R T1Done", pReportSize);
            lLocalState = 1;
            lReturn = true;
         }
         break;

	  case	CProtocol::STATE_UNKNOWN:
      default:
         lLocalState = 0;
         lReturn = false;
      }
   }




   return lReturn; 
}

#endif


#ifdef __NO_T2_

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT2(SMC::CClient::ReceptionStatus        //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessT2(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   static int lState = 0;

   //if (pReceptionStatus == CClient::rsNewReportRequired)
   if(pPayloadPtr->Src!=CProtocol::T2)
   {  
      switch(pPayloadPtr->State)
      {
      case CProtocol::InitT2:
         if(lState != 1)
         {
            strncpy(pReportStr, "T2 SMC R T2Ready T2Moving=0 T2MoveComplete=0", pReportSize); 
            lState = 1;
            lReturn = true;
         }

         break;
            
      case CProtocol::T2GotoDelivery:
         if(pPayloadPtr->Conditions[CProtocol::T2Moving]==CProtocol::eFALSE && lState < 2)
         {
            strncpy(pReportStr, "T2 SMC R T2Moving", pReportSize);
            lState = 2;
            lReturn = true;
         }
         else
         if(lState <3)
         {
            strncpy(pReportStr, "T2 SMC R T2MoveComplete T2Moving=0", pReportSize); 
            lState = 3;
            lReturn = true;
         }

         break;
            
      case CProtocol::T2GotoSupply:
         if(pPayloadPtr->Conditions[CProtocol::T2Moving]==CProtocol::eFALSE && lState < 4)
         {
            strncpy(pReportStr, "T2 SMC R T2Moving", pReportSize); 
            lState = 4;
            lReturn = true;
         }
         else
         if(lState < 5)
         {
            strncpy(pReportStr, "T2 SMC R T2MoveComplete T2Moving=0", pReportSize);
            lState = 5;
            lReturn = true;
         }
         break;

      case CProtocol::T2Finish:
         if(lState < 10)
         {
            strncpy(pReportStr, "T2 SMC R T2Done", pReportSize); 
            lReturn = true;
            lState = 10;
         }
		 break;

   
	  case CProtocol::STATE_UNKNOWN:
      default:
         lReturn = false;
         lState = 0;
         break;
      } //swcase
   } //if

   return lReturn;
}

#endif


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT2(SMC::CClient::ReceptionStatus        //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessIAD(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   if (pReceptionStatus == CClient::rsNewReportRequired || pReceptionStatus == CClient::rsStillReportRequired)
   {
	   if(pPayloadPtr->State == CProtocol::IADFinish)
            strncpy(pReportStr, "IAD SMC R IADDone", pReportSize);
	   else
			strncpy(pReportStr, "IAD SMC R IADReady", pReportSize);

	   lReturn = true;
   }


   if(pPayloadPtr->Src!=CProtocol::IAD)
   {  
      switch(pPayloadPtr->State)
      {
      case CProtocol::InitIAD:
         if(!pPayloadPtr->Conditions[CProtocol::IADReady])
         {
            strncpy(pReportStr, "IAD SMC R IADReady IADMoving=0 IADMoveComplete=0", pReportSize); 
            lReturn = true;
         }

         break;
       
	  case CProtocol::MoveToReadyPosition:
	  case CProtocol::MoveToHandoverPosition:
//	  case CProtocol::MoveIADToReadyPosition:
//      case CProtocol::MoveIADToHandoverPosition:
		    strncpy(pReportStr, "IAD SMC R IADMoving IADMoveComplete", pReportSize);
            lReturn = true;
         break;


	  case CProtocol::MoveToRestPosition:
	  case CProtocol::FetchApproach1:
	  case CProtocol::FetchApproach2:
	  case CProtocol::FetchApproach3:
	  case CProtocol::Fetch1:
	  case CProtocol::Fetch2:
	  case CProtocol::Fetch3:
	  case CProtocol::Retract1:
	  case CProtocol::Retract2:
	  case CProtocol::Retract3:
		  strncpy(pReportStr, "IAD SMC R IADMoveComplete IADMoving=0", pReportSize);
		  lReturn = true;
		  break;

	  case CProtocol::Inspection1:
	  case CProtocol::Inspection2:
		  strncpy(pReportStr, "IAD SMC R IADMoveComplete IADMoving=0", pReportSize);
		  lReturn = true;
		  break;

	  case CProtocol::PointToFaultyPart1:
		  strncpy(pReportStr, "IAD SMC R IADMoveComplete IADMoving=0", pReportSize);
		  //lState = 7;
		  lReturn = true;
		  break;


      case CProtocol::IADFinish:
         //if(lState < 10)
         //{
            strncpy(pReportStr, "IAD SMC R IADDone IADReady", pReportSize); 
            lReturn = true;
         //   lState = 10;
         //}

         break;

      case CProtocol::STATE_UNKNOWN:
      default:
         //lReturn = false;
         //lState = 0;
         break;
      } //swcase
   } //if

   return lReturn;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT2(SMC::CClient::ReceptionStatus        //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessKUKA(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   //static int lState = 0;

   //if (pReceptionStatus == CClient::rsNewReportRequired)

   if (pReceptionStatus == CClient::rsNewReportRequired || pReceptionStatus == CClient::rsStillReportRequired)
   {
	   strncpy(pReportStr, "", pReportSize); 
	   lReturn = true;
   }

   if(pPayloadPtr->Src!=CProtocol::KUKA)
   {  
      //DO we should simulate T2Moving for realistic duration
      //actually just sending the T2Moving once...

      switch(pPayloadPtr->State)
      {
      case CProtocol::InitKUKA:
       //  if(lState != 1)
       //  {
            strncpy(pReportStr, "KUKA SMC R KUKAReady", pReportSize); 
       //     lState = 1;
            lReturn = true;
        // }

         break;
      
  	  case CProtocol::MoveToReadyPosition:
	  case CProtocol::MoveToHandoverPosition:
		  /*
         if(pPayloadPtr->Conditions[CProtocol::KUKAMoving]==CProtocol::eFALSE && lState < 2)
         {
            strncpy(pReportStr, "KUKA SMC R KUKAMoving", pReportSize);
            lState = 2;
            lReturn = true;
         }
         else
         if(lState <3)
         {
			 */
            strncpy(pReportStr, "KUKA SMC R KUKAMoveComplete KUKAMoving=0", pReportSize); 
            //lState = 3;
            lReturn = true;
         //}

         break;
            
      case CProtocol::MoveToRestPosition:
         if(!pPayloadPtr->Conditions[CProtocol::KUKAMoveComplete])
         {
            strncpy(pReportStr, "KUKA SMC R KUKAMoveComplete", pReportSize); 
            //lState = 4;
            lReturn = true;
         }
		 /*
         else
         if(lState < 5)
         {
            strncpy(pReportStr, "KUKA SMC R KUKAMoveComplete KUKAMoving=0", pReportSize);
            lState = 5;
            lReturn = true;
         }
		 */
         break;

	  case CProtocol::PathPlanning:
		  if(!pPayloadPtr->Conditions[CProtocol::PathOK])
		  {
			  strncpy(pReportStr, "KUKA SMC R PathOK=1", pReportSize);
			  lReturn = true;
		  }

		  break;


	  case CProtocol::Inspection1:
	  case CProtocol::Inspection2:
			  strncpy(pReportStr, "KUKA SMC R KUKAMoveComplete KUKAMoving=0", pReportSize);
			  //lState = 5;
			  lReturn = true;
			  break;

	  case CProtocol::PointToFaultyPart1:
		  strncpy(pReportStr, "KUKA SMC R KUKAMoveComplete KUKAMoving=0", pReportSize);
		  //lState = 7;
		  lReturn = true;
		  break;

	  case CProtocol::AcknowledgeRequest:
		  //step 7.2.1
		  strncpy(pReportStr, "KUKA SMC R KUKAMoveComplete", pReportSize);
		  lReturn = true;
		  break;

	  case CProtocol::FetchApproach1:
	  case CProtocol::FetchApproach2:
	  case CProtocol::FetchApproach3:
	  case CProtocol::Fetch1:
	  case CProtocol::Fetch2:
	  case CProtocol::Fetch3:
	  case CProtocol::Retract1:
	  case CProtocol::Retract2:
	  case CProtocol::Retract3:
		  //if(!pPayloadPtr->Conditions[CProtocol::PathOK])
		  {
			  strncpy(pReportStr, "KUKA SMC R KUKAMoveComplete KUKAMoving=0", pReportSize);
			  lReturn = true;
		  }

		  break;

      case CProtocol::FinishKUKA:
        // if(lState < 10)
        // {
            strncpy(pReportStr, "KUKA SMC R KUKADone", pReportSize); 
            lReturn = true;
        //    lState = 10;
        // }

         break;

	  case	CProtocol::STATE_UNKNOWN:
      default:
         //lReturn = false;
         //lState = 0;
         break;
      } //swcase
   } //if

   return lReturn;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessGRIP(SMC::CClient::ReceptionStatus        //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessGRIP(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   //static int lState = 0;

   if (pReceptionStatus == CClient::rsNewReportRequired || pReceptionStatus == CClient::rsStillReportRequired)
   {
	   strncpy(pReportStr, "GRIP SMC R GRIPReady", pReportSize); 
	   lReturn = true;
   }
 
#ifdef _TOTO_
   switch(pPayloadPtr->Conditions[CProtocol::GRIPPosition])
   {
   case 0: //Close
	   if(!pPayloadPtr->Conditions[CProtocol::GRIPClose])
		   strncpy(pReportStr, "GRIP SMC R GRIPClose", pReportSize); 
	   lReturn = true;
	   break;

	   /*
   case 1: //CloseNormal
	   if(!pPayloadPtr->Conditions[CProtocol::GRIPCloseNormal])
		  strncpy(pReportStr, "GRIP SMC R GRIPCloseNormal", pReportSize); 
	   lReturn = true;
	   break;
	   */

   case 2: //Open
	   if(!pPayloadPtr->Conditions[CProtocol::GRIPOpen])
		   strncpy(pReportStr, "GRIP SMC R GRIPOpen", pReportSize); 
	   lReturn = true;
	   break;

	   /*
   case 3: //OpenNormal
	   if(!pPayloadPtr->Conditions[CProtocol::GRIPOpenNormal])
		  strncpy(pReportStr, "GRIP SMC R GRIPOpenNormal", pReportSize); 
	   lReturn = true;
	   break;
	   */

   case 4: //OneFinger
	   if(!pPayloadPtr->Conditions[CProtocol::GRIPOneFinger])
			strncpy(pReportStr, "GRIP SMC R GRIPOneFinger", pReportSize); 
	   lReturn = true;
	   break;

   default:
	   strncpy(pReportStr, "GRIP SMC R GRIPMoving", pReportSize); 
	   lReturn = true;
	   break;
   }
#endif

   if(pPayloadPtr->Src!=CProtocol::GRIP)
   {  
      switch(pPayloadPtr->State)
      {
      case CProtocol::InitGRIP:
         if(!pPayloadPtr->Conditions[CProtocol::GRIPReady])
         {
            strncpy(pReportStr, "GRIP SMC R GRIPReady", pReportSize); 
            //lState = 1;
            lReturn = true;
         }

         break;
            
      case CProtocol::TapDetector:
		  if(!pPayloadPtr->Conditions[CProtocol::TapDetected])
		  {
			  strncpy(pReportStr, "GRIP SMC R TapDetected", pReportSize);
			  lReturn = true;
		  }
		  break;

	  case CProtocol::Handover:
		  if(!pPayloadPtr->Conditions[CProtocol::HandoverComplete])
		  {
			  strncpy(pReportStr, "GRIP SMC R HandoverComplete", pReportSize);
			  lReturn = true;
		  }
		  break;

	  case CProtocol::OpenGRIP:
		  if(!pPayloadPtr->Conditions[CProtocol::GRIPOpen])
		  {
			  strncpy(pReportStr, "GRIP SMC R GRIPOpen", pReportSize);
			  lReturn = true;
		  }
		  break;


		case CProtocol::BiasGRIP:
				break;


		case CProtocol::FetchApproach1:
		case CProtocol::FetchApproach2:
		case CProtocol::FetchApproach3:
		if(!pPayloadPtr->Conditions[CProtocol::GRIPOpen])
		{
			strncpy(pReportStr, "GRIP SMC R GRIPOpen", pReportSize); 
			lReturn = true;
		}
		break;
            

	  case CProtocol::CloseGRIP:
	  case CProtocol::CloseTipGRIP:
	  case CProtocol::MoveToRestPosition:
		  if(!pPayloadPtr->Conditions[CProtocol::GRIPClose])
		  {
            strncpy(pReportStr, "GRIP SMC R GRIPClose", pReportSize);
            lReturn = true;
		  }
         break;

		case CProtocol::OneFingerGRIP:
		  if(!pPayloadPtr->Conditions[CProtocol::GRIPOneFinger])
		  {
            strncpy(pReportStr, "GRIP SMC R GRIPOneFinger", pReportSize);
            lReturn = true;
		  }
		  break;

      case CProtocol::FinishGRIP:
         if(!pPayloadPtr->Conditions[CProtocol::GRIPReady])
		 {
            strncpy(pReportStr, "GRIP SMC R GRIPReady", pReportSize); 
            lReturn = true;
         }
         break;

	  case CProtocol::STATE_UNKNOWN:
      default:
      //   lReturn = false;
         //lState = 0;
         break;
      } //swcase
   } //if

   return lReturn;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT3P(SMC::CClient::ReceptionStatus       //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessT3P(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   static int lStateCheck = 0;
   UNUSED static int lStateIterate = 0;
   //static int lStateTaken = 0;
   UNUSED static int lStateFinish = 0;

   //if(pPayloadPtr->Src==CProtocol::T3P)
   //   return lReturn; 

   //required responses ????????
   //if (pReceptionStatus == CClient::rsNewReportRequired || pPayloadPtr->State == CProtocol::Iterate || pPayloadPtr->State == CProtocol::T1DeliverPart)

   if (pReceptionStatus == CClient::rsNewReportRequired || pReceptionStatus == CClient::rsStillReportRequired)
   {
	   strncpy(pReportStr, "", pReportSize); 
	   lReturn = true;
   }

   if(pPayloadPtr->Src!=CProtocol::T3P)
   {
      //From SMCProtocol.h
         //T3P respond to ALL -> state Iterate, //R NextPart // R AssemblyComplete

      /* For T3P:
            InitT3P,
            CheckParts,
            FinishT3P,
      */

      /* From T3P:
            T3PInProgress,
            T3PReady, xx
            PartOnTray,
            PartInPlace,
            PartTaken,
            AssemblyComplete,
            T3PFailed,
      */

      switch(pPayloadPtr->State)
      {
         case CProtocol::InitT3P:
            lStateFinish = 0;
            lStateIterate = 0;
            //lStateTaken = 0;
            if(lStateCheck < 1)
            {
               strncpy(pReportStr, "T3P SMC R T3PReady", pReportSize);
               lStateCheck = 1;
               lReturn = true;  
            }
            break;

         case CProtocol::FinishT3P: 
            lStateCheck = 0;
            //lStateTaken = 0;
            lStateIterate = 0;
            if(lStateCheck < 1)
            {
               strncpy(pReportStr, "T3P SMC R T3PReady", pReportSize);
               lStateFinish = 1;
               lReturn = true; 
            }
            break;

         case CProtocol::CheckParts:
            if(pPayloadPtr->Conditions[CProtocol::T3PInProgress] == CProtocol::eFALSE && lStateCheck < 2)
            {
               strncpy(pReportStr, "T3P SMC R T3PInProgress", pReportSize);
               lStateCheck = 2;
               lReturn = true;
            }
            else
            if(pPayloadPtr->Conditions[CProtocol::PartOnTray] == CProtocol::eFALSE && lStateCheck < 3)
            {
               strncpy(pReportStr, "T3P SMC R PartOnTray", pReportSize);    //CheckPart completes with PartOnTray
               lStateCheck = 3;
               lReturn = true;
            }
            break;

/*
         case CProtocol::T1DeliverPart:
            lStateCheck = 0;
            lStateIterate = 0;
            lStateFinish = 0;
            //PartOnTray detected by T3P in a dedicated state
            //PartTaken must be detected here for this state to end
            if(pPayloadPtr->Conditions[CProtocol::PartTaken]==CProtocol::eFALSE && lStateTaken < 1)
            {
               //Not sure if I send it at the right time
               //it must be simply sent before Iterate or inside Iterate (for nextPart/AssemblyComplete)
               strncpy(pReportStr, "T3P SMC R PartTaken", pReportSize);
               lStateTaken = 1;
               lReturn = true;
            }
            break;
*/

         case CProtocol::Iterate:
            lStateFinish = 0;
            lStateCheck = 0;
            if(pPayloadPtr->Conditions[CProtocol::PartCount] < SUPPLY_CYCLES) // && lStateIterate < 7) //max 2 parts
            {
               //strncpy(pReportStr, "T3P SMC R NextPart\n", pReportSize);
               sprintf(pReportStr, "T3P SMC R NextPart %d", pPayloadPtr->Conditions[CProtocol::PartCount]+1);
               lStateIterate = 7;
               lReturn = true;
            }
            else
            if(pPayloadPtr->Conditions[CProtocol::PartCount] >= SUPPLY_CYCLES) // && lStateIterate < 7)
            {
               strncpy(pReportStr, "T3P SMC R AssemblyComplete", pReportSize);
               lStateIterate = 7;
               lReturn = true;
            }
            else   
            if(pPayloadPtr->Conditions[CProtocol::PartOnTray]==CProtocol::eTRUE && pPayloadPtr->Conditions[CProtocol::PartTaken]==CProtocol::eTRUE)
            {
               //Not sure if I send it at the right time
               //it must be simply sent before Iterate or inside Iterate (for nextPart/AssemblyComplete)
               strncpy(pReportStr, "T3P SMC R PartInPlace", pReportSize);
               lStateIterate = 6;
               lReturn = true;
            }

            /*
            else
            if(pPayloadPtr->Conditions[CProtocol::WaitingForPickup]==CProtocol::eTRUE && pPayloadPtr->Conditions[CProtocol::PartOnTray]==CProtocol::eTRUE & lState < 7)
            {
               strncpy(pReportStr, "T3P SMC R PartTaken\n", pReportSize); 
               lState = 7;
               lReturn = true;
            } 
            */

            break;

/*
         case CProtocol::T1RetractTray:
            //this one should occur after PartTaken
            lStateCheck = 0;
            lStateIterate = 0;
            lStateFinish = 0;
            lStateTaken = 0;
            break;
*/

	     case CProtocol::STATE_UNKNOWN:
         default:
            lStateCheck = 0;
            lStateIterate = 0;
            lStateFinish = 0;
            //lStateTaken = 0;
            break;
      }

   }

   return lReturn; 
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT3K(SMC::CClient::ReceptionStatus       //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessT3K(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   //static int lState = 0;

   if (pReceptionStatus == CClient::rsNewReportRequired || pReceptionStatus == CClient::rsStillReportRequired)
   {
	   if(pPayloadPtr->Conditions[CProtocol::T3KReady]==CProtocol::eFALSE)
			strncpy(pReportStr, "T3K SMC R T3KReady", pReportSize);
	   else
			strncpy(pReportStr, "", pReportSize);
	   lReturn = true;
   }	   
	   
   if (pPayloadPtr->Src!=CProtocol::T3K)
   {
      switch(pPayloadPtr->State)
      {
      case CProtocol::InitT3K:
      case CProtocol::FinishT3K:
         if(pPayloadPtr->Conditions[CProtocol::T3KReady]==CProtocol::eFALSE)
         {
            strncpy(pReportStr, "T3K SMC R T3KReady", pReportSize);
            //lState = 1;
            lReturn = true;
         }
         break;

	  case	CProtocol::STATE_UNKNOWN:
      default:
         //lState = 0;
         break;

      } //swcase
   } //if


   return lReturn; 
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT3W(SMC::CClient::ReceptionStatus       //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessT3W(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   static int lState = 0;

   if (pReceptionStatus == CClient::rsNewReportRequired || pReceptionStatus == CClient::rsStillReportRequired)
   {
	   strncpy(pReportStr, "T3W SMC R T3WReady WorkerPresent WorkerInMainWorkspace WorkerHandUp WorkerInSideWorkspace WorkerReadyForPart", pReportSize); 
	   lReturn = true;
   }


   if (pPayloadPtr->Src!=CProtocol::T3W)
   {
      switch(pPayloadPtr->State)
      {

      case CProtocol::InitT3W:
      case CProtocol::FinishT3W:
         //if(pPayloadPtr->Conditions[CProtocol::T3WReady]==CProtocol::eFALSE)
         {
            strncpy(pReportStr, "T3W SMC R T3WReady", pReportSize);
            lState = 1;
            lReturn = true;
         }
         break;

      case CProtocol::CheckWorker:
         if(pPayloadPtr->Conditions[CProtocol::T3WInProgress] == CProtocol::eFALSE && lState < 2)
         {
            strncpy(pReportStr, "T3W SMC R T3WInProgress", pReportSize); 
            lState = 2;
            lReturn = true;
         }
         else
         if(lState < 20)
         {
            lState++;
            if(lState%6 == 0)
            {
               strncpy(pReportStr, "T3W SMC R T3WInProgress", pReportSize);
               lReturn = true;
            }
         }
         else
         if(pPayloadPtr->Conditions[CProtocol::WorkerPresent] == CProtocol::eFALSE && lState < 21)
         {
            strncpy(pReportStr, "T3W SMC R WorkerPresent", pReportSize); 
            lState = 21;
            lReturn = true;
         }
       
         break;

	  case CProtocol::HumanReady:
		  strncpy(pReportStr, "T3W SMC R WorkerInMainWorkspace=1 WorkerReadyForPart=1", pReportSize); 
		  lReturn = true;
		  break;

	  case CProtocol::HumanReadyToReceive:
		  strncpy(pReportStr, "T3W SMC R WorkerReadyForPart=1 WorkerInMainWorkspace=1", pReportSize); 
		  lReturn = true;
		  break;

	  case CProtocol::RequestReplacement:
		  strncpy(pReportStr, "T3W SMC R WorkerHandUp=1 WorkerInMainWorkspace=1", pReportSize); 
		  lReturn = true;
		  break;

	  case CProtocol::IndicateDone:
		  strncpy(pReportStr, "T3W SMC R WorkerAssemblyDone=1 WorkerInSideWorkspace=1", pReportSize); 
		  lReturn = true;
		  break;

	  case	CProtocol::STATE_UNKNOWN:
      default:
         break;

      } //swcase
   } //if

   return lReturn; 
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool InTheLoopProcessT3O(SMC::CClient::ReceptionStatus       //
//               pReceptionStatus, char* pReportStr, int pReportSize, const   //
//               SMC::CProtocol::tSMCPayload* pPayloadPtr)                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool SMCClient::InTheLoopProcessT3O(SMC::CClient::ReceptionStatus pReceptionStatus, char* pReportStr, int pReportSize, const SMC::CProtocol::tSMCPayload* pPayloadPtr)
{
   bool  lReturn = false;

   //static int lState = 0;

   if (pReceptionStatus == CClient::rsNewReportRequired || pReceptionStatus == CClient::rsStillReportRequired)
   {
	   strncpy(pReportStr, "T3O SMC R T3OReady FreeSpace=1", pReportSize); 
	   lReturn = true;
   }

   if(pPayloadPtr->Src!=CProtocol::T3O)
   {
      switch(pPayloadPtr->State)
      {
      case CProtocol::InitT3O:
         if(!pPayloadPtr->Conditions[CProtocol::T3OReady]) 
         {
            strncpy(pReportStr, "T3O SMC R T3OReady", pReportSize);
            //lState = 1;
            lReturn = true;
         }
         break;

	  case CProtocol::StartCollisionCheck: 
		  //strncpy(pReportStr, "T3O SMC R FreeSpace=0 NoSpace=1", pReportSize);
		 
		  strncpy(pReportStr, "T3O SMC R FreeSpace=1 NoSpace=0", pReportSize);
		  //lState = 1;
		  lReturn = true;
		  break;

	  case CProtocol::CollisionAvoidance:
      case CProtocol::CheckFreeSpace:

		  /*
         if(pPayloadPtr->Conditions[CProtocol::T3OInProgress]==CProtocol::eFALSE && lState != 2)
         {
            strncpy(pReportStr, "T3O SMC R NoSpace", pReportSize);
            lState = 2;
            lReturn = true;
         }
         else
		 */
         if(!pPayloadPtr->Conditions[CProtocol::FreeSpace])
         {
            strncpy(pReportStr, "T3O SMC R FreeSpace", pReportSize);
            //lState = 11;
            lReturn = true;
         }
         break;

		 /*
      case CProtocol::CheckFreeSpaceS:
         if(pPayloadPtr->Conditions[CProtocol::T3OInProgress]==CProtocol::eFALSE)
         {
            strncpy(pReportStr, "T3O SMC R T3OInProgress", pReportSize);
            lState = 10;
            lReturn = true;
         }
         else
         if(pPayloadPtr->Conditions[CProtocol::T3OInProgress]==CProtocol::eTRUE)
         {
            {
               strncpy(pReportStr, "T3O SMC R FreeSpaceToSupply", pReportSize);
               lState = 15;
               lReturn = true;
            }
         }
		 */

         /*
         else
         if (pPayloadPtr->Conditions[CProtocol::T3OInProgress]==CProtocol::eFALSE)
         {
            strncpy(pReportStr, "T3O SMC R FreeSpaceToSupply\n", pReportSize);
            lState = 19;
            lReturn = true;
         }
         */

         break;

      case CProtocol::FinishT3O:
         if(!pPayloadPtr->Conditions[CProtocol::T3OReady]) 
         {
            strncpy(pReportStr, "T3O SMC R T3OReady", pReportSize);
            //lState = 20;
            lReturn = true;
         }
         break;

	  case	CProtocol::STATE_UNKNOWN:
      default:
         //lState = 0;
         break;
      }
   }

   return lReturn; 
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void PrintParametersHelp(const char * pAppName)              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void SMCClient::PrintParametersHelp(const char * pAppName)
{
   cout << "Error: use -c host:port [Options]" << endl; 
   cout << endl;
   cout << "Options: " << endl;
   cout << "   -c <SMC server address>:<SMC port> (may be 127.0.0.1:4010 for instance)" << endl;
   //cout << "   -module <SMCModule name> (T1, T2, T3, T3P, T3W or T3O)" << endl;
   //cout << "   -SMC (enable SMC normal behavior)" << endl;
   cout << "   -SADB (enable SADB normal behavior)" << endl;
   //cout << "   -T1 (enable T1 normal behavior)" << endl;
   //cout << "   -T2 (enable T2 normal behavior)" << endl;
   cout << "   -IAD (enable IAD normal behavior)" << endl;
   cout << "   -KUKA (enable KUKA normal behavior)" << endl;
   cout << "   -GRIP (enable GRIP normal behavior)" << endl;
   cout << "   -T3K (enable T3K normal behavior)" << endl;
   cout << "   -T3P (enable T3P normal behavior)" << endl;
   cout << "   -T3W (enable T3W normal behavior)" << endl;
   cout << "   -T3O (enable T3O normal behavior)" << endl;
   //cout << "   -wait ms (For server only. Default=10)" << endl;
   //cout << "   -max <MaxIterations>" << endl;
   cout << "   -autorecon ms <delay> (min 1000 for a 1s delay). Auto reconnection delay. (Default don't retry to reconnect automatically)" << endl;
   cout << "   -maxrecon <# of retry> (Default=0 for infinit loop when the -autoreconnect parameter is present)" << endl;
   cout << "   -verbose <verbose level> (0 for mute, 1 a little, ... Default = 1)";
   cout << endl;
   cout << "Example: " << endl;
   cout << "   " << pAppName << " -c 127.0.0.1:4010 -module T1" << endl;
}

//end of SMCClientSim.cpp


