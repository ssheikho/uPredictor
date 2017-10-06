// ProjetVS2008.cpp : Defines the entry point for the console application.
//

#include <SADB-Client/SADB.h>

#include "SMCServer.h"
#include "SMC/Server.h"

#ifdef WIN32
#include <windows.h> //for Sleep()
#define msleep(A) Sleep(A)
#else
#define msleep(A) usleep((A)*1000.0) 
#endif

#include <stdlib.h>
#include <iostream>
#include "string.h"

//***SADBClient stuff
#include "SADBClient.h"

using namespace std;
using namespace SMC;

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int main(int argc, char* argv[])                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
   SMCServer lSMCServer;
   int lReturn = lSMCServer.main(argc, argv);
   exit(lReturn);
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : Params()                                                     //
//                                                                            //
// DESCRIPTION : Constructor                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

SMCServer::Params::Params() 
   :  mServerPort(4010)
   , mMaxIterations(0)
   , mNClients(15)
   , mStackSize(1000)
   , mTimeout(1000)
   , mScript(NULL)
   , mVerboseLevel(1)
   , mSADBServer(0)
   , mSADBPort(4001)  //put real default port here
   , mParamsOk(false)
{
   strncpy(mName, "SMCsvr", 128);
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int main(int argc, char* argv[])                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int SMCServer::main(int argc, char* argv[])
{
   bool lRunning = true;

   //float lStartTime = 0.0;

   double lInitTime = 0.0;


   //arguments
   if (!ParseParameters(argc, argv))
      return 0;


   ////////////////////////
   ////// SMC server //////
   ////////////////////////

   CServer lSMCServer(mParams.mName, mParams.mServerPort, mParams.mNClients, mParams.mStackSize, sizeof(CProtocol::tSMCPayload), CProtocol::MaxMessageLen, mParams.mVerboseLevel - 1); 
   CProtocolServer lProtocoleServer(mParams.mScript, mParams.mVerboseLevel - 1);

   if (!lProtocoleServer.IsOpen())
   {
      cerr << "*** Error: ProtocoleSever is not open !!" << endl;
      return -1;
   }

   unsigned int lFrameNumber = 0;

   lInitTime = lSMCServer.GetInitTime();
   cout << "Starting " << " server at T=" << lSMCServer.getTime(lInitTime) << endl;

   //SADB Stuff Inits

   SADBClient *lSADB = new SADBClient(mParams.mSADBServer?mParams.mSADBServer:"", mParams.mSADBPort);
   
   lSADB->SetCategory("SMC.Infos","Stuff published by SMC Server");

   for (int iModuleId = 0 ; iModuleId < lProtocoleServer.GetNbModules() ; iModuleId++)
	   lSADB->PublishString2(format("SMC.Names.Module%02d", iModuleId), lProtocoleServer.GetModuleName(iModuleId));

   for (int iStateId = 0 ; iStateId < lProtocoleServer.GetNbStates() ; iStateId++)
	   lSADB->PublishString2(format("SMC.Names.State%02d", iStateId), lProtocoleServer.GetStateName(iStateId));

   for (int iCond = 0 ; iCond < lProtocoleServer.GetNbConditions() ; iCond++)
		lSADB->PublishString2(format("SMC.Names.Cond%02d", iCond), lProtocoleServer.GetConditionName(iCond));

   for(int lCol=0; lCol<lProtocoleServer.GetNbTableColumns(); lCol++)
	   lSADB->PublishString2(format("SMC.StateTable.Names.Col%02d", lCol), lProtocoleServer.GetTableColumnName(lCol));

   for(int lRow=0; lRow<lProtocoleServer.GetNbTableRows(); lRow++)
		   for(int lCol=0; lCol<lProtocoleServer.GetNbTableColumns(); lCol++)
			   lSADB->PublishString2(format("SMC.StateTable.Row%03d.Col%02d", lRow, lCol), lProtocoleServer.GetTableElement(lRow,lCol));

   //*** SADB *** publish some useful parameters to others: ip, port
   lSADB->PublishString("SMC.Params.ServerName", mParams.mName);
   lSADB->PublishInteger("SMC.Params.ServerPort", mParams.mServerPort);
   lSADB->PublishString("SMC.Params.SADBName", mParams.mSADBServer);
   lSADB->PublishInteger("SMC.Params.SADBPort", mParams.mSADBPort);
   lSADB->PublishString("SMC.Params.SrcriptFile", mParams.mScript);
 
   //*** SADB event ****
   lSADB->PublishDouble("SMC.InitTime", lInitTime); //value is InitTime, timestamp is recording time (from SADB)
  
   // Mandatory module list
   bool lIsConnected[CProtocol::NbSMCModules]; 
	
   // Init
   for (int iModule = 0 ; iModule < lProtocoleServer.GetNbModules() ; iModule++)
	   lIsConnected[iModule] = false;

   bool lIsClientResponse = false;

      while(lRunning)
      {
         //////////////////////////////////////////////////////////////////////////
         ////// Check if allOk (All mandatory client presents and all at last frame
         //////////////////////////////////////////////////////////////////////////
          // AllOk is eFALSE if one client in late or if one of the mandatory clients is disconnected (or not yet connected)
         bool lIsClientLate = false;
         bool lIsClientDisconnected = false;

		 
         // Init mandatory module list to false
         for (int iModule = 0 ; iModule < lProtocoleServer.GetNbModules() ; iModule++)
            lIsConnected[iModule] = false;
		 

      lSMCServer.LockReports();

      if (mParams.mVerboseLevel > 0)
         cout << "F#" << (lFrameNumber);

      if (lSMCServer.mReports.size() == 0)
      {
         lIsClientDisconnected = true;

         if (mParams.mVerboseLevel > 0)
            cout << ": No client connected, ";
      }
      else
      {
         // Scan all connected client reports
         for(unsigned int iReport = 0; iReport < lSMCServer.mReports.size(); iReport++)
         {
            CServer::tReport &lReport = *lSMCServer.mReports[iReport];

            if (lReport.LastTransmittedFrame != lFrameNumber) //BUG: AllOk alternates True/False 
			//if (lReport.LastTransmittedFrame < lFrameNumber-1)
            {
               lIsClientLate = true;

               if (mParams.mVerboseLevel > 0)
                  cout << " " << lReport.Header.Name << " at frame #" << lReport.LastTransmittedFrame;
            }

			int lModule = CProtocol::GetModuleId(lReport.Header.Name);

			if(lModule == CProtocol::NONE || lModule == CProtocol::UNKNOWN )
				cout << "WARNING! Unknown Module " << lReport.Header.Name << endl;
			else
				lIsConnected[lModule] = true;

         } // End for each report
      } // End if at least on client connected

      lSMCServer.UnlockReports();

      // Scan all mandatory module 
      if (!lIsClientDisconnected)
      {
         for (int iModule = 0 ; iModule < CProtocol::NbSMCModules ; ++iModule)
         {
			 // Validate only mandatory modules 
			 if( CProtocol::IsMandatoryModule(iModule) && !lIsConnected[iModule] )
			 {

				 if (mParams.mVerboseLevel > 0)
				 {
					 if (!lIsClientDisconnected)
						 cout << "Module ";
					 else
						 cout << ", ";

					 cout << CProtocol::GetModuleName(iModule);
				 }

				 lIsClientDisconnected = true;
			
			 }
			 
         } // End for

         if (lIsClientDisconnected && mParams.mVerboseLevel > 0)
            cout << " not connected";
      }


      lProtocoleServer.mPayload.Conditions[CProtocol::AllOk] = (lIsClientLate || lIsClientDisconnected ? CProtocol::eFALSE: CProtocol::eTRUE);

      if (mParams.mVerboseLevel > 0)
      {
         cout << ", AllOk=" << (int)lProtocoleServer.mPayload.Conditions[CProtocol::AllOk];  // (lProtocoleServer.mPayload.Conditions[CProtocol::AllOk] ==  CProtocol::eTRUE ? "eTRUE" : "eFALSE");
         cout << ", S=" << lProtocoleServer.GetStateName(lProtocoleServer.mPayload.State);
		// cout << ", R=" << lProtocoleServer.mPayload.Step;
		 cout << ", Step=" << lProtocoleServer.GetTableElement(lProtocoleServer.mPayload.Step, CProtocolServer::ColStep); 
		 cout << endl;
      }


      //////////////////////////////////////////////////////////////////
      ////// Send the new state if necessary or if timeout or first time
      //////////////////////////////////////////////////////////////////

      if (lProtocoleServer.EvaluateState() || !lIsClientResponse)
      {
         memcpy(lSMCServer.getPayloadBuffer(), &lProtocoleServer.mPayload, sizeof(CProtocol::tSMCPayload));

         if (mParams.mVerboseLevel > 1)
            cout << "F#" << lFrameNumber + 1 << " to push: \"" << lProtocoleServer.mPayload.Message << "\"" << endl;

		 double lTime = lSMCServer.getTime();

         lSMCServer.PushData(++lFrameNumber);
         if (mParams.mVerboseLevel == 0)
            cout << ". "; // Just to confirm that server is running

		 //*** SADB push message (state transition or repeat)
		 //PublishString("SMC.StateTransition", lProtocoleServer.mPayload.Message, lSMCServer.getHeader()->TimeStamp); //TS may not be valid->getTime() is O
		 if(strlen(lProtocoleServer.mPayload.Message)>0 )
		 {
			 lSADB->PublishString("SMC.Message", lProtocoleServer.mPayload.Message,lTime); //human readable
			 lSADB->PublishBytes("SMC.Payload", (const char*)&lProtocoleServer.mPayload, sizeof(CProtocol::tSMCPayload),lTime); //human + computer readable
			 TrackChanges(lProtocoleServer, lSADB, lTime);
		 }

      }

      ////// Wait a new back payload in the list
      lIsClientResponse = lSMCServer.WaitNextClientReport(mParams.mTimeout);
      if (!lIsClientResponse) // A timeout occurred the send an empty message
      {
         lProtocoleServer.mPayload.Src = CProtocol::SMC; //DO ------- SMC -CHECK----------------------
         lProtocoleServer.mPayload.Dst = CProtocol::ALL; //DO ------- ALL -CHECK----------------------

         continue; // Go wait the next client report or timeout
      }

      ////////////////////////////////////////////////
      ////////////// Get Access back payload list here
      ////////////////////////////////////////////////

      lSMCServer.LockBackPayloadList();
      {
         CServer::tBackPayloadList & lBackPayloadList = lSMCServer.mBackPayloadList;
         CServer::tBackPayloadList::iterator lBackPayloadIter;

         // Scan all back payload to push them back to clients
         for (lBackPayloadIter = lBackPayloadList.begin() ; lBackPayloadIter != lSMCServer.mBackPayloadList.end() ; lBackPayloadIter++)
         {

			 //*** must find mPayloadTS value for SADB ***

            //////////////////////////
            ////// Parse back payload
            //////////////////////////
            if (mParams.mVerboseLevel > 0)
               cout << "BackPayload: --- \"" << (*lBackPayloadIter).c_str() << "\" --------" << endl;

            if ( !lProtocoleServer.ParseMessage((*lBackPayloadIter).c_str()) )
               continue;

            ////////////////////////////////////
            ////// Write payload and push report
            ////////////////////////////////////
            {
               memcpy(lSMCServer.getPayloadBuffer(), &lProtocoleServer.mPayload, sizeof(CProtocol::tSMCPayload));

			   double lTime = CServer::getTime();

               if (mParams.mVerboseLevel > 1)
                  cout << "At " << CServer::getTime(lInitTime) << " Report F#" << lFrameNumber + 1 << " to push: \"" << lProtocoleServer.mPayload.Message << "\"" << endl;

               lSMCServer.PushData(++lFrameNumber);

			   lSADB->PublishString("SMC.Message", lProtocoleServer.mPayload.Message, lTime); //human readable
			   lSADB->PublishBytes("SMC.Payload", (char*)&lProtocoleServer.mPayload, sizeof(CProtocol::tSMCPayload), lTime); //human + computer readable
			   
			   TrackChanges(lProtocoleServer, lSADB, lTime);
			   //***SADB Publish Message*** (copy from clients... maybe easier from client threads... we have header)
			   //PublishString("SMC.Report", lProtocoleServer.mPayload.Message, lProtocoleServer.mPayloadTS)
			   //lSADB->PublishString("SMC.Report.Message", lProtocoleServer.mPayload.Message, lTime); //human readable
			   //lSADB->PublishBytes("SMC.Report.Payload", (char*)&lProtocoleServer.mPayload, sizeof(CProtocol::tSMCPayload), lTime); //human + computer readable

            }
         } // End mBackPayloadList scan

         lBackPayloadList.clear();
      }
      lSMCServer.UnlockBackPayloadList();

   } // End while running


   //*** SADB event ****
   double lStopTime = lSMCServer.getTime();
   lSADB->PublishDouble("SMC.StopTime", lStopTime, lStopTime);
   lSADB->PublishDouble("SMC.RunningTime", lSMCServer.getTime(lInitTime), lStopTime);

   cout << "Stopping server at " << lSMCServer.getTime(lInitTime) << endl;
   if (mParams.mVerboseLevel > 0)
      cout << "Halt... " << endl;

   lSMCServer.halt();

   if (mParams.mVerboseLevel > 0)
      cout << "Close... " << endl;

   lSMCServer.close();

   cout << "Server closed" << endl;

   return 0;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int ParseParameters(int argc, char* * argv)                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int SMCServer::ParseParameters(int argc, char* * argv)
{
   Params lParams;

   for(int i = 1; i < argc; i++)
   {
      if(!strcmp(argv[i], "-s"))
      {
         if (++i >= argc)
         {
            cerr << "SMCServer app: Invalid parameter -s. Server port number is missing." << endl;
            mParams.mParamsOk = false;
            break;
         }

         lParams.mServerPort = atoi(argv[i]);
         lParams.mParamsOk = true;
         continue;
      } // End if -s


      if(!strcmp(argv[i], "-max"))
      {
         if (++i >= argc)
         {
            cerr << "SMCServer app: Invalid parameter -max. Maximum number of iteration is missing." << endl;
            mParams.mParamsOk = false;
            break;
         }

         lParams.mMaxIterations = atoi(argv[i]);
         continue;
      } // End if -max


      if(!strcmp(argv[i], "-n"))
      {
         if (++i >= argc)
         {
            cerr << "SMCServer app: Invalid parameter -n. Server name is missing." << endl;
            mParams.mParamsOk = false;
            break;
         }

         strcpy(lParams.mName, argv[i]);
         continue;
      } // End if -n


      if(!strcmp(argv[i], "-script"))
      {
         if (++i >= argc)
         {
            cerr << "SMCServer app: Invalid parameter -script. Script file name is missing." << endl;
            mParams.mParamsOk = false;
            break;
         }

         if (lParams.mScript)
            delete lParams.mScript;

         lParams.mScript = new char[strlen(argv[i]) + 1];
         strcpy(lParams.mScript, argv[i]);
         continue;
      } // End if -script


      if(!strcmp(argv[i], "-clients"))
      {
         if (++i >= argc)
         {
            cerr << "SMCServer app: Invalid parameter -clients. Maximum number of clients is missing." << endl;
            mParams.mParamsOk = false;
            break;
         }

         lParams.mNClients = atoi(argv[i]);

         if (lParams.mNClients < 5) 
            lParams.mNClients = 5;

         continue;
      } // End if -clients

      if(!strcmp(argv[i], "-stack"))
      {
         lParams.mStackSize = atoi(argv[i+1]);
         i++;

         if (lParams.mStackSize < 1) 
            lParams.mStackSize = 1;
      }

      if(!strcmp(argv[i], "-timeout"))
      {
         lParams.mTimeout = atoi(argv[i+1]);
         i++;

         if (lParams.mTimeout < 1) 
            lParams.mTimeout = 20;
      }

      if(!strcmp(argv[i], "-verbose"))
      {
         if (++i >= argc)
         {
            cerr << "SMCServer app: Invalid parameter -max. Verbose level is missing." << endl;
            mParams.mParamsOk = false;
            break;
         }

         lParams.mVerboseLevel = atoi(argv[i]);

         if (lParams.mTimeout < 1) 
            lParams.mTimeout = 20;

         continue;
      } // End if -verbose

	  if(!strcmp(argv[i], "-sadbserver"))
	  {
		  if (++i >= argc)
		  {
			  cerr << "SMCServer app: Invalid parameter -sadbserver. Verbose level is missing." << endl;
			  mParams.mParamsOk = false;
			  break;
		  }

		  if (lParams.mSADBServer)
			  delete lParams.mSADBServer;

		  lParams.mSADBServer = new char[strlen(argv[i]) + 1];
		  strcpy(lParams.mSADBServer, argv[i]);
		  continue;
	  } // End if -verbose

	  if(!strcmp(argv[i], "-sadbport"))
	  {
		  lParams.mSADBPort = atoi(argv[i+1]);
		  i++;
	  }

   } // End for

   if (!lParams.mParamsOk)
   {
      PrintParametersHelp(argv[0]);
      return false;
   }


   mParams = lParams; // Params are then copy to the real one

   if (lParams.mVerboseLevel > 0)
   {
      cout << "SMC Server parameters:" << endl;
      cout << "Verbose level = " << lParams.mVerboseLevel << endl;
      cout << "Name = \"" << lParams.mName << "\"" << endl;
      cout << "CSV Script filename = \"" << lParams.mScript << "\"" << endl;
      
      cout << "Port = " << lParams.mServerPort << endl;

      if (lParams.mMaxIterations > 0)
         cout << "Max iterations = " << lParams.mMaxIterations << endl;

      cout << "Maximum number of clients = " << lParams.mNClients << endl;
      cout << "FIFO stack size = " << lParams.mStackSize << endl;
      cout << "Timeout = " << lParams.mTimeout << endl;
	  
	  cout << "SADBServer = " << lParams.mSADBServer << endl;
	  cout << "SADBPort = " << lParams.mSADBPort << endl;

   } // End if verbose

   return true;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void PrintParametersHelp(const char * pAppName)              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void SMCServer::PrintParametersHelp(const char * pAppName)
{
   cout << "Error: use -s port [Options] (default port is " << mParams.mServerPort << ")" << endl;
   cout << endl;
   cout << "Options: " << endl;
   cout << "   -sadbserver <SADB server name or ip> (empty = operate without server)" << endl;
   cout << "   -sadbport <SADB server port> (default port is " << mParams.mSADBPort << ")" << endl;
   cout << "   -max <MaxIterations> (for debug only)" << endl;
   cout << "   -n server name (Default=\"" << mParams.mName << "\"" << endl;
   cout << "   -script <ScriptFilename.csv>" << endl;
   cout << "   -clients <max number of clients> (Default=" << mParams.mNClients << ")" << endl;
   cout << "   -stack <stacksize> (Default=" << mParams.mStackSize << ")" << endl;
   cout << "   -timeout ms (Default=" << mParams.mTimeout << ")" << endl;
   cout << "   -verbose <verbose level> (0 for mute, 1 a little, ... Default = " << mParams.mVerboseLevel << ")";
   cout << endl;
   cout << "Example: " << endl;
   cout << "   " << pAppName << " -s " << mParams.mServerPort << " -n SMCsrv -timeout 500 -stack 100" << endl;
}

bool SMCServer::TrackChanges(CProtocolServer &pServer, SADBClient* pSADB, double pTime)
{
	static bool lInitialized = false;

	static SMC::CProtocol::tSMCPayload lPreviousPayload;

	static double lCurrentStateBeginTime = 0.0; 
	static double lCurrentStepBeginTime = 0.0;
	static double lConditionTime[SMC::CProtocol::NbSMCConditions];

	if(!lInitialized)
	{
		SMC::CProtocolServer::InitSMCPayload(lPreviousPayload);

		lCurrentStateBeginTime = pTime;
		lCurrentStepBeginTime  = pTime;
		for (int iCondId = 0; iCondId < SMC::CProtocol::NbSMCConditions; iCondId++)
			lConditionTime[iCondId]=pTime;

		lInitialized = true;
	}

	if(!pSADB)
		return false;

	//type, source, dest

	//trap step changes
	//step (state table position = line number in script)
	if(pServer.mPayload.Step!=lPreviousPayload.Step)
	{
		pSADB->PublishString("SMC.Step", pServer.GetStepName(pServer.mPayload.Step),pTime); //store StepId (or script line number) & timestamp
		pSADB->PublishDouble(format("SMC.Begin.Step.%s", pServer.GetStepName(pServer.mPayload.Step)), pTime-lCurrentStepBeginTime, pTime); //prev duration & TS = begin time per distinct StepId (3 digits) 
		pSADB->PublishDouble(format("SMC.End.Step.%s", pServer.GetStepName(lPreviousPayload.Step)), pTime-lCurrentStepBeginTime, pTime); //duration & time (in TS) per StepId (3 digits)
		lCurrentStepBeginTime = pTime;
	}

	//trap state changes
	if(pServer.mPayload.State!=lPreviousPayload.State)
	{
		//pSADB->PublishInteger("SMC.StateId", (int)pServer.mPayload.State, pTime); //step change -> store StateId code & timestamp
		pSADB->PublishString("SMC.StateName", pServer.GetStateName(pServer.mPayload.State), pTime); //store StateName & timestamp
		pSADB->PublishDouble(format( "SMC.Begin.%s", pServer.GetStateName(pServer.mPayload.State)), pTime, pTime); //BeginTime per StateId (2 digits)
		pSADB->PublishDouble(format("SMC.End.%s", pServer.GetStateName(lPreviousPayload.State)), pTime-lCurrentStateBeginTime, pTime); //duration & time (in TS) per StateId (2 digits)
		lCurrentStateBeginTime = pTime;
	}

	//trap individual condition changes (per CondId and per CondName)
	//conditions & counters
	for(int iCondId=0; iCondId < pServer.GetNbConditions(); iCondId++ )
		if(pServer.mPayload.Conditions[iCondId]!=lPreviousPayload.Conditions[iCondId])
		{
			//totally generic (no use)
			//pSADB->PublishInteger(format("SMC.Value.Cond%02d", iCondId), (int)pServer.mPayload.Conditions[iCondId],pTime); //condition Value & TS=BeginTime per CondId
			//pSADB->PublishDouble(format("SMC.Begin.Cond%02d.Val%d", iCondId,pServer.mPayload.Conditions[iCondId]), pTime-lConditionTime[iCondId] ,pTime);
			//pSADB->PublishDouble(format("SMC.End.Cond%02d.Val%d", iCondId,lPreviousPayload.Conditions[iCondId]), pTime-lConditionTime[iCondId] ,pTime); //condition duration & TS=EndTime per CondId
			
			//real name, Val + previous duration, begin/end time
			pSADB->PublishInteger(format("SMC.Value.%s", pServer.GetConditionName(iCondId),(int)lPreviousPayload.Conditions[iCondId]), (int)pServer.mPayload.Conditions[iCondId],pTime); //condition Value & TS=BeginTime per CondId
			pSADB->PublishDouble(format("SMC.Begin.%s.Val%d",pServer.GetConditionName(iCondId),(int)pServer.mPayload.Conditions[iCondId]),pTime-lConditionTime[iCondId],pTime); // Condition Value & TS=BeginTime per CondName
			pSADB->PublishDouble(format("SMC.End.%s.Val%d", pServer.GetConditionName(iCondId),lPreviousPayload.Conditions[iCondId]), pTime-lConditionTime[iCondId],pTime); //condition duration & TS=EndTime per CondId
			lConditionTime[iCondId] = pTime;
		}

	memcpy(&lPreviousPayload, &pServer.mPayload, sizeof(SMC::CProtocol::tSMCPayload));

	return true;
}
