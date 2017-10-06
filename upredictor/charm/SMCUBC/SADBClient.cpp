//SADBClient.cpp
//
// Denis Ouellet - May 2014 
//Description: stuff to communicate with SADB

#include "SADBClient.h"

/*
SADBClient::SADBClient()
{
}
*/

using namespace std;

SADBClient::SADBClient(const std::string &pServerAdrress, const int pPort): 
	mBoard(0),
	mGeneralCategory(0)
{

	//DO NOTE: we made sure at upper level to call constructor with empty string ("") wnen char* = NULL.

	if(pServerAdrress.empty())
	{
		cout << "WARNING: No SADB server specified. running without SADB." << endl;
		return;  //NOTE: mBoard remains 0 afterwards
	}

	try{

		mBoard = (SADB::Blackboard*) new (SADB::Blackboard);
		
		int lReturnCode = mBoard->ConnectToServer(pServerAdrress.c_str(), pPort);

		cout << "Connecting to SADB " << pServerAdrress.c_str() << ":" << pPort << "..." << endl;

		//if failed?
		if(lReturnCode!=0)
		{
			cerr << "mBoard->ConnectToServer() returned value=" << lReturnCode << endl;
			//delete mSADB;
			//mSADB = NULL;
			return;
		}
	}
	catch(exception lExc)
	{
		cout << "SADBClient Exception = " << lExc.what() << endl;

	}
	catch(...)
	{
		cout << "SADBClient Exception Inconnue! " << endl;
	}

	//Normal case
	return;
}

SADBClient::~SADBClient()
{
	cout << "Free() SADB client object list (with "<< mIndex.size() <<" objects)..." << endl;
	for(std::vector<SADB::BlackboardObject*>::iterator iIterator=mIndex.begin(); iIterator!=mIndex.end(); iIterator++ )
		(*iIterator)->Free();
	mIndex.clear();

	if(!mBoard)
		return;

	cout << "Disconnect() from SADB..." << endl;
	try{
		mBoard->Disconnect();
		mBoard->Free();
		delete mBoard;
		mBoard=NULL; 
	}
	catch(exception e)
	{
		cout << "~SADBClient() Exception = " << e.what() << endl;

	}
	catch(...)
	{
		cout << "~SADBClient() Exception Inconnue! " << endl;
	}

	cout << "SADB Disconnected." << endl;

}

int SADBClient::ConnectToServer(const std::string &pAddress, const int pPort)
{
	return mBoard->ConnectToServer(pAddress.c_str(), pPort);
}


bool SADBClient::Disconnect()
{
	mBoard->Disconnect();

	return true;
}

void SADBClient::SetCategory(const std::string &pCategoryName, const std::string &pCategoryDescription)
{
	if(!mBoard)
		return;

	if(!pCategoryName.empty())
	{
		mGeneralCategory = mBoard->CreateCategoryIfNonExistant(pCategoryName.c_str());
		if(!pCategoryDescription.empty())
			mBoard->SetCategoryDescription(mGeneralCategory, pCategoryDescription.c_str());
	}
}

bool SADBClient::SetObjectCategory(const std::string &pName, const std::string &pCategoryName, const std::string &pCategoryDescription)
{
	if(!mBoard)
		return false;

	SADB::SADBu64 lCategory = 0;

	if(!pCategoryName.empty())
	{
		lCategory = mBoard->CreateCategoryIfNonExistant(pCategoryName.c_str());

		if(!pCategoryDescription.empty())
			mBoard->SetCategoryDescription(lCategory, pCategoryDescription.c_str());
	}

	SADB::BlackboardObject *lObject = SearchObject(pName);
	if(!lObject || !lCategory)
		return false;

	lObject->AddToCategory(lCategory);

	return true;
}


size_t SADBClient::PublishBytes(const std::string &pName, const char* pMessage, size_t pSize, double pTime)
{
	if(!mBoard)
		return 0;

	SADB::BlackboardObject* lObjet = SearchObjectBeforeCreate(pName, "bytes", SADB::BOByte);
	if(!lObjet)
		return 0;

	//Update
	lObjet->SetTimestamp(ConvertTimestamp(pTime));

	lObjet->SetDimensions(1,(SADB::SADBu32 *)&pSize);
	for(size_t i=0; i<pSize; i++)
		lObjet->SetByte(pMessage[i],i);

	lObjet->Send();

	return pSize;
}

size_t SADBClient::PublishString(const std::string &pName, const std::string pString, double pTime)
{
	if(!mBoard)
		return 0;

	SADB::BlackboardObject* lObjetStr = SearchObjectBeforeCreate(pName, "string", SADB::BOByte);
	if(!lObjetStr)
		return 0;

	//Update
	lObjetStr->SetTimestamp(ConvertTimestamp(pTime));
	lObjetStr->SetString(pString.c_str());
	lObjetStr->Send();

	return pString.length();
}


//\brief set description with content (more useful for info about settings... web readable)
size_t SADBClient::PublishString2(const std::string &pName, const std::string pString, double pTime)
{
	if(!mBoard)
		return 0;

	SADB::BlackboardObject* lObjetStr = SearchObjectBeforeCreate(pName, pString, SADB::BOByte);
	if(!lObjetStr)
		return 0;

	lObjetStr->SetDescription(pString.c_str());

	//Update
	lObjetStr->SetTimestamp(ConvertTimestamp(pTime));
	lObjetStr->SetString(pString.c_str());
	lObjetStr->Send();

	return pString.length();
}

size_t SADBClient::ReadString(const std::string &pName, std::string &pString, double &pTime)
{
	if(!mBoard)
		return 0;

	SADB::BlackboardObject* lObjet = SearchObjectBeforeGet(pName, SADB::BOByte);
	if(!lObjet)
		return 0;

	lObjet->GetLatestValue();
	pString.assign(lObjet->GetString());
	pTime = lObjet->Time.Get();

	return pString.length();
}

bool SADBClient::PublishDouble(const std::string &pName, const double &pVal, double pTime)
{
	if(!mBoard)
		return false;

	SADB::BlackboardObject* lObjetDouble = SearchObjectBeforeCreate(pName, "double", SADB::BODouble, 1);
	if(!lObjetDouble)
		return false;

	lObjetDouble->SetTimestamp(ConvertTimestamp(pTime));
	lObjetDouble->SetDouble(pVal,0);
	lObjetDouble->Send();

	return true;
}

double SADBClient::ReadDouble(const std::string &pName, double &pTime)
{
	double lVal = 0.0;

	if(mBoard==NULL)
		return lVal;

	SADB::BlackboardObject* lObjetDouble = SearchObjectBeforeGet(pName, SADB::BODouble);
	if(!lObjetDouble)
		return false;

	lObjetDouble->SetDimensionsf(1,1);//1 val

	lObjetDouble->GetLatestValue();
	//lObjetDouble->CheckForNewValue();

	SADB::Timestamp lTimeR;
	lTimeR.Now();
	lVal = lObjetDouble->GetDouble(0);
	pTime = lObjetDouble->Time.Get();
	cout << "ReadDouble(" << pName.c_str() << ")= " << lVal << " Tw=" << pTime << " Tr=" << ConvertTimestamp(lTimeR) << endl;

	return lVal;
}


bool SADBClient::PublishInteger(const std::string &pName, const int &pVal, double pTime)
{
	if(mBoard==NULL)
		return false;

	SADB::BlackboardObject* lObjet = SearchObjectBeforeCreate(pName, "int", SADB::BOInteger, 1);
	if(!lObjet)
		return false;

	lObjet->SetTimestamp(ConvertTimestamp(pTime));
	lObjet->SetInteger(pVal,0);
	lObjet->Send();

	return true;
}

int SADBClient::ReadInteger(const std::string &pName, double &pTime)
{
	int lVal = 0;

	if(mBoard==NULL)
		return lVal;

	SADB::BlackboardObject* lObjet = SearchObjectBeforeGet(pName, SADB::BOInteger);
	if(!lObjet)
		return lVal;

	lObjet->SetDimensionsf(1,1);//1 val

	lObjet->GetLatestValue();

	SADB::Timestamp lTimeR;
	lTimeR.Now();
	lVal = lObjet->GetInteger(0);
	pTime = lObjet->Time.Get();
	cout << "ReadInteger(" << pName.c_str() << ")= " << lVal << " Tw=" << pTime << " Tr=" << ConvertTimestamp(lTimeR) << endl;

	return lVal;
}


/*
bool SADBClient::PublishInteger(const char *pName, const int &pValue, double pTimestamp)
{
	if(mBoard==NULL)
		return false;

	SADB::BlackboardObject lObjetDouble;
	lObjetDouble.Create(mBoard, pName, "integer", SADB::BOInteger);
	lObjetDouble.SetDimensionsf(1,1);//1 val
	//lObjetDouble.SetDescription("integer");
	lObjetDouble.AddToCategory(mGeneralCategory);
	lObjetDouble.SetTimestamp(ConvertTimestamp(pTimestamp));
	lObjetDouble.SetInteger(pValue,0);
	lObjetDouble.Send();
	lObjetDouble.Free();

	return true;
};
*/
/*
int SMC::CProtocol::SADBConnect(const char* pServer)
{
	//Blackboard Board;
	if(mSADB)
		delete mSADB;

	mSADB = new Blackboard();
	mSADB->ConnectToServer(pServer);

	return 1;
}
*/

/*
int SMC::CProtocol::SADBDisconnect()
{

	if(mSADB)
	{
		mSADB->Disconnect();
		delete mSADB;
	}
	mSADB = NULL;

	return 1;
}
*/

/*
int SMC::CProtocol::SADBAddString(const char* pName, const char* pString, const char* pDescription)
{
	unsigned int lLen = strlen(pString)+1; 

	BlackboardObject lString;
	lString.SetBlackboard(mSADB);
	lString.SetDataType(BOByte);
	lString.SetDimensionsf(1,lLen);
	lString.AddToBlackboard();
	for(unsigned int j=0; j<lLen; j++)
		lString.SetByte( pString[j], j );
	
	lString.SetTimestampNow();
	lString.SetName(pName);

	if(pDescription)
		lString.SetDescription(pDescription);
	
	lString.Send();

	return lLen;
}
*/


/*
int SMC::CProtocol::SADBGetString(const char* pName, char* &pString)
{
	int lLen = 0;

	BlackboardObject lRead;

	lRead.SetBlackboard(mSADB);
	lRead.GetByName(pName);
	lRead.SetName(pName); //DO Name is not set after GetByName
	lRead.SetDataType(BOByte);
	lRead.GetLatestValue();

	lLen = lRead.TotalNumberOfElements;

	if(pString==NULL)
		pString = new char[lLen+1];

	for(int k=0; k<lLen; k++)
		pString[k] = (char)lRead.GetByte(k);

	return lLen;
}
*/


/*
void SMC::CProtocol::SADBAddInteger(const char* pName, const int pValue, const char* pDescription)
{
	BlackboardObject lInteger;
	lInteger.SetBlackboard(mSADB);
	lInteger.SetDataType(BOInteger);
	lInteger.SetDimensionsf(1,1);
	lInteger.AddToBlackboard();

	lInteger.SetInteger(pValue);

	lInteger.SetTimestampNow();
	lInteger.SetName(pName);

	if(pDescription)
		lInteger.SetDescription(pDescription);

	lInteger.Send();

	return;
}
*/

/*
int  SMC::CProtocol::SADBGetInteger(const char* pName)
{
	int lValue = 0;

	BlackboardObject lRead;

	lRead.SetBlackboard(mSADB);
	lRead.GetByName(pName);
	lRead.SetName(pName);
	lRead.SetDataType(BOInteger);
	lRead.GetLatestValue();

	lValue = lRead.GetInteger(1);

	return lValue;
}
*/

/*
int SMC::CProtocol::SADBAddByteArray(const char* pName, const char* pBytes, int pLen, const char* pDescription)
{ 
	BlackboardObject lString;
	lString.SetBlackboard(mSADB);
	lString.SetDataType(BOByte);
	lString.SetDimensionsf(1,pLen);
	lString.AddToBlackboard();

	for(int j=0; j<pLen; j++)
		lString.SetByte( pBytes[j], j );

	lString.SetTimestampNow();
	lString.SetName(pName);

	if(pDescription)
		lString.SetDescription(pDescription);

	lString.Send();

	return pLen;
}
*/

/*
int SMC::CProtocol::SADBGetByteArray(const char* pName, char* &pBytes, int &pLen)
{ 
	int lLen = 0;

	BlackboardObject lRead;

	lRead.SetBlackboard(mSADB);
	lRead.GetByName(pName);
	lRead.SetName(pName);
	lRead.SetDataType(BOByte);
	lRead.GetLatestValue();

	lRead.Dimensions;

	lLen = lRead.TotalNumberOfElements;

	if(pBytes==NULL)
		pBytes = new char[lLen+1];

	for(int k=0; k<lLen; k++)
		pBytes[k] = lRead.GetByte(k);

	pLen = lLen;

	return lLen;
}
*/

/*
int SMC::CProtocol::SADBAddStringArray(const char* pName, const char* pStrings[], int pNbStrings, const char* pDescription)
{
	unsigned int lMaxLen = 0; 

	BlackboardObject lString;
	lString.SetBlackboard(mSADB);
	lString.SetDataType(BOByte);

	//find max len
	for(int i=0; i<pNbStrings; i++)
		lMaxLen = max(strlen(pStrings[i])+1, lMaxLen);

	lString.SetDimensionsf(2, pNbStrings, lMaxLen);

	lString.AddToBlackboard();
	unsigned int j = 0;
	for(int i=0; i<pNbStrings; i++)
	{
		for(j=0; j<strlen(pStrings[i])+1; j++)
			lString.SetByte( pStrings[i][j], i, j );

		for(; j<lMaxLen; j++) //padding with 0s
			lString.SetByte( 0, i, j );
	}

	lString.SetTimestampNow();
	lString.SetName(pName);

	if(pDescription)
		lString.SetDescription(pDescription);

	lString.Send();

	return lMaxLen*pNbStrings;
}
*/

/*
int SMC::CProtocol::SADBGetStringArray(const char* pName, char** &pStrings, int &pNbStrings, int &pLen)
{
	int lMaxLen = 0;
	int i=0;
	int j=0;

	SADBStringTable lRead;

	lRead.SetBlackboard(mSADB);
	lRead.GetByName(pName);
	lRead.SetName(pName); //DO Name is not set after GetByName?
	//lRead.SetDataType(BOByte);
	lRead.GetLatestValues();

	pNbStrings = lRead.nRows; //lRead.Dimensions[1];
	pLen = lMaxLen = lRead.nCols; //lRead.Dimensions[0];

	if(pStrings)
		delete [] pStrings;

	pStrings = new char* [pNbStrings];

	for(i=0; i<pNbStrings; i++)
	{
		pStrings[i] = new char[lMaxLen];

		for(j=0; j<lMaxLen; j++)
			pStrings[i][j] = lRead.GetString(j, i);
	}

	return lMaxLen*pNbStrings;
}
*/

/*
int SMC::CProtocol::SADBAddStringArray2D(const char* pName, const char*** pStrings, int pNbRows, int pNbColumns, const char* pDescription)
{
	UINT lMaxLen = 0; 

	BlackboardObject lString;
	lString.SetBlackboard(mBoard);
	lString.SetDataType(BOByte);

	//find max len
	for(int i=0; i<pNbRows; i++)
		for(int j=0; j<pNbColumns; j++)
			lMaxLen = max(strlen(pStrings[i][j])+1, lMaxLen);

	lString.SetDimensionsf(3, pNbRows, pNbColumns, lMaxLen);

	lString.AddToBlackboard();
	UINT k = 0;
	for(int i=0; i<pNbRows; i++)
	{
		for(int j=0; j<pNbColumns; j++)
		{
			for(k=0; k<strlen(pStrings[i][j])+1; k++)
				lString.SetByte( pStrings[i][j][k], i, j, k );

			for(; k<lMaxLen; k++) //padding with 0s
				lString.SetByte( 0, i, j, k );
		}
	}

	lString.SetTimestampNow();
	lString.SetName(pName);

	if(pDescription)
		lString.SetDescription(pDescription);

	lString.Send();

	return lMaxLen*pNbRows*pNbColumns;
}
*/

/*
void SMC::CProtocol::InitSADB()
{
	  cout << "SADB Inits..." << endl;
	  
	  //check connection failure / wait / while ready ?????????

	  //SADBu64 lLabels = mSADB->CreateCategory();
	  //mSADB->SetCategoryName(lLabels,"SMC");
	  //mSADB->SetCategoryDescription(lLabels,"Stuff for SMC");

	  //SMC Enum


	  //SADBAddString("Hello Name", "hello World!");
	  //SADBAddString("Hello 2 Name", "hello World 2!");

	  //enum columnID {eModuleID, eActualStateID, eNextStateID, eFailStateID, ePrimCondID, eSecCondID, eFailCondID, eRepeatTimeout, eMaxMatrixColumns};

	  //const int NbStateTableColumns = 8;
	  //const char* StateColumnsNames[] = {"ModuleID", "ActualStateID", "NextStateID", "FailStateID", "PrimCondID", "SecCondID", "FailCondID", "RepeatTimeout"};
	  //SADBAddStringArray("SMC.StateTable.Columns.Names", StateColumnsNames, NbStateTableColumns);

	  //SADBStringTable ColumnNames;

	  //const char* SMCBoolNames[] = {"FALSE", "TRUE", "NA"};
	  //SADBAddStringArray("SMC.Bool.Names", SMCBoolNames, 3);

	  //const int NbSMCModules = 9;

	  //const char* SMCModulesNames[] = {"SMC", "T1", "T2", "T3", "T3P", "T3W", "T3O", "ALL", "UNKNOWN"};
	  mModules = new SADBStringTable;
	  mModules->SetBlackboard(mSADB);
	  mModules->LoadCSV("SMC.Modules.csv");
	  mNbModules = mModules->nRows - 1;

	  //SADBAddStringArray("SMC.Modules.Names", SMCModulesNames, NbSMCModules);
	  //SADBAddInteger("SMC.Modules.Count", NbSMCModules);

	  //const char SMCMandatoryModules[] = {1, 0, 0, 0, 1, 1, 1, 0, 0}; //bool flags indicating which modules should be present for AllOk
	  //SADBAddByteArray("SMC.Modules.Names", SMCMandatoryModules, mNbModules);

	  	  //SMC State

	  const int NbSMCStates = 24;
	  const char* SMCStateNames[] = {
		  "Begin", 
		  "InitT1", 
		  "T1DeliverPart", 
		  "FinishT1", 
		  "InitT2", 
		  "T2GotoSupply", 
		  "T2GotoDelivery", 
		  "T2Finish", 
		  "InitT3W", 
		  "CheckWorker", 
		  "FinishT3W", 
		  "InitT3P",
		  "CheckParts",
		  "FinishT3P",
		  "InitT3O",
		  "CheckFreeSpaceS",
		  "CheckFreeSpaceD",
		  "FinishT3O",
		  "Iterate",
		  "Finish",
		  "T1RetractTray",
		  "NextState",
		  "PreviousState",
		  "RepeatState"
	  };
	*/

	  //SADBAddStringArray("SMC.States.Names", SMCStateNames, NbSMCStates);

	  /*
	  const int NbSMCConditions = 33;
	  const char* lSMCConditionNames[] = {"AllOk", "NextPart", 
		 "T1Ready",  "WaitingForWorker", "PresentingPart", "WaitingForPickup", "PartPickedUp", "RetractingTray",  "TrayRetracted", "T1Done", "T1Failed", 
		 "T2Ready", "T2Moving", "T2MoveComplete", "T2Done", "T2Failed", 
		 "T3WInProgress", "T3WReady", "WorkerPresent", "T3WFailed", 
		 "T3PInProgress", "T3PReady", "PartOnTray", "PartInPlace", "PartTaken", "AssemblyComplete", "T3PFailed", 
		 "T3OInProgress", "T3OReady", "FreeSpaceToSupply", "FreeSpaceToDeliver", "T3OFailed", "NONE"
	  };
	  */

	  /*
	  mConditions = new SADBStringTable;
	  mConditions->SetBlackboard(mSADB);
	  mConditions->LoadCSV("SMC.Conditions.csv");
	  mNbConditions = mConditions->nRows - 1;
	  */



	  	  //SMC State Table Column
	  /*
	   SADBAddStringArray("SMC.Conditions.Names", lSMCConditionNames, NbSMCConditions);
	   const int NbStateTransitions = 21;
	   static const char* lStateMatrix[NbStateTransitions][NbStateTableColumns] = {
		   {"ALL", "Begin"            , "NextState"         , "Finish"    , "AllOk"             , "-1" ,  "-1", "60"}, //just load modules
		   {"T3O", "InitT3O"          , "NextState"         , "Finish"    , "T3OReady"          , "-1" ,  "-1", "0"},
		   {"T3W", "InitT3W"          , "NextState"         , "FinishT3O" , "T3WReady"          , "-1" ,  "T3WFailed", "0"}, //T3WReady, T3WFailed
		   {"T3P", "InitT3P"          , "NextState"         , "FinishT3W" , "T3PReady"          , "-1" ,  "-1", "0"}, 
		   {"T2 ", "InitT2"           , "NextState"         , "FinishT3P" , "T2Ready"           , "-1" ,  "-1", "0"},
		   {"T1 ", "InitT1"           , "NextState"         , "T2Finish"  , "T1Ready"           , "-1" ,   "T1Failed", "0"}, //Inits completed

		   {"T3W", "CheckWorker"      , "NextState"         , "FinishT1"  , "WorkerPresent"     , "-1" ,   "-1" , "10"}, //  T3WInProgress, WorkerPresent, T3WFailed

		   {"T3P", "CheckParts"       , "NextState"         , "FinishT1"  , "PartOnTray"        , "-1" ,   "-1" , "10"}, //T3PInProgress, PartOnTray
		   {"T3O", "CheckFreeSpaceD"  , "NextState"         , "FinishT1"  , "FreeSpaceToDeliver", "-1" ,   "-1" , "10"}, //goto worker
		   {"T2 ", "T2GotoDelivery"   , "NextState"         , "FinishT1"  , "T2MoveComplete"    , "-1" ,   "-1" , "0"},
		   {"T1 ", "T1DeliverPart"    , "NextState"         , "FinishT1"  , "T1Done"            , "PartTaken" ,   "T1Failed", "0"}, //Deliver part (super state)

		   //sub states:
		   //1)x WaitingForWorker		  -> T3W SMC R WorkerPresent
		   //2) PresentingPart		     -> T1  SMC R PresentingPart


		   //3) WaitingForPickup		  -> T3P SMC R PartTaken
		   //PartPickedUp	(event)		  -> T1  SMC R PartPickedUp

		   {"T1 ", "T1RetractTray"    , "NextState"         , "FinishT1"  , "TrayRetracted"     , "-1" ,   "T1Failed", "0"}, //Tray retract (added DO + Amir)

		   //4) RetractingTray			  -> T1  SMC R RetractingTray
		   //TrayRetracted (event)	 	  -> T1  SMC R TrayRetracted
		   //T1Done	 (event) - final response	(normal)		  
		   //T1Failed (event)	- final report (failure)		   

		   {"T3O", "CheckFreeSpaceS"  , "NextState"         , "FinishT1"  , "FreeSpaceToSupply", "-1",   "-1" , "10"}, //return to supply
		   {"T2 ", "T2GotoSupply"     , "NextState"         , "FinishT1"  , "T2MoveComplete",    "-1",   "-1" , "0"},
		   {"ALL", "Iterate"          , "CheckWorker"       , "FinishT1"  , "NextPart",          "-1",   "AssemblyComplete", "0"}, //iterate: check with T3 if assembly is completed or not

		   {"T1 ", "FinishT1"         , "NextState"         , "T2Finish"  , "T1Done",            "-1",   "T1Failed", "0"},  //Task complete, start cleanup
		   {"T2 ", "T2Finish"         , "NextState"         , "FinishT3P" , "T2Done",            "-1",   "-1", "0"},
		   {"T3P", "FinishT3P"        , "NextState"         , "FinishT3W" , "T3PReady",          "-1",   "-1", "0"}, //T3PInProgress, T3PReady
		   {"T3W", "FinishT3W"        , "NextState"         , "FinishT3O" , "T3WReady",          "-1",   "-1", "0"},
		   {"T3O", "FinishT3O"        , "NextState"         , "Finish"    , "T3OReady",          "-1",   "-1", "0"},
		   {"ALL", "Finish"           , "Begin"             , "Begin"     , "-1",                "-1",   "-1", "0"}      //go back to init (maybe we have Restart and Quit)
	   }; 
	   */

	  /*
	   char lName[128];
	   for(int m=0; m<mNbStateTransitions; m++)
	   {
		   
		   for(int n=0; n< 8; n++)
		   {
			   sprintf(lName, "SMC.StateTable.State.%02d.%02d",m , n);   
			   SADBAddByteArray(lName, lStateMatrix[m][n], strlen(lStateMatrix[m][n])+1);
		   }
		   

		   sprintf(lName, "SMC.StateTable.State.%02d",m);
		   SADBAddStringArray(lName, lStateMatrix[m], NbStateTableColumns);

	   }
	   */
	   //this should help to read the table
	   /*
	   sprintf(lName, "SMC.StateTable.NbStateTransitions");
	   SADBAddInteger(lName, NbStateTransitions);
	   */

	   //SADBAddStringArray2D(lName, (const char***)lStateMatrix, NbStateTransitions, NbStateTableColumns); //not working


	  //SMC Condition


	  /*
	  SADBu64 lStateMachine = mBoard->CreateCategory();
	  mBoard->SetCategoryName(lStateMachine,"SMC.StateMachine");
	  mBoard->SetCategoryDescription(lStateMachine,"State table for SMC");
	  */

/*
	  BlackboardObject lSMCStateMachine;
	  lSMCStateMachine.SetBlackboard(mSADB);
	  lSMCStateMachine.SetDataType(BOInteger);//table of integers
	  lSMCStateMachine.SetDimensionsf(1,7);//1 dimensional vector, 3 components
	  lSMCStateMachine.SetName("SMC.StateMachine");
	  lSMCStateMachine.SetDescription("State table for SMC");
	  lSMCStateMachine.AddToBlackboard();
	  */

	  //cout << "SADB Inits completed." << endl;

	 // cout << "SADB Test Read..." << endl;

	  //char* lBuf4 = NULL;
	  //SADBGetString("Hello Name", lBuf4);

	  //cout << "lRead: " << lBuf4 << endl;

	  /*
	  char** lStateTableColumns = NULL;
	  int lNbStateTableColumns = 0; 
	  int lWidth = 0;
	  */
	  //SADBGetStringArray("SMC.StateTable.Columns.Names", lStateTableColumns, lNbStateTableColumns, lWidth);

 // 	  cout << "SADB Test Read completed." << endl;
	  
//}



/*
int SMC::CProtocol::getNbConditions()
{
	int lResult = 0;

	if(!mConditions)
		return lResult;

	if(mConditions->nRows < 1)
		return lResult;
	
	if(mConditions->nCols <= 1)
		return lResult;
	
	const char * lString = mConditions->GetString(ColumnNames,RowHeaders);

	if(strcmp(lString, "ConditionName"))
	{
		cout << "Not a list of conditions!" << endl;
		return lResult;
	}

	lResult = mConditions->nRows-1; //Nb lignes - ligne 0 au debut

	mNbConditions = lResult;

	return lResult;
}
*/

/*
int SMC::CProtocol::getConditionId(const char* pName)
{
	int lResult = 0; //0 means FIRST, should be on AllOK flag

	if(!mModules)
		return lResult;

	if(strcmp("ConditionName", mModules->GetString(ColumnNames,RowHeaders)))
	{
		cout << "Object is not a list of Conditions!" << endl;
		return lResult;
	}

	int lNbModules = getNbModules(); //0 is not there

	for(int lRow=1; lRow<lNbModules; lRow++)
	{			
		const char * lString = mModules->GetString(ColumnNames, lRow);

		if(!strcmp(pName, mModules->GetString(ColumnNames, lRow)))
		{
			lResult = lRow-1; //return the row - 1 (to have position in array)
			return lResult;
		}
	}

	return lResult;

}
*/

/*
const char* SMC::CProtocol::getConditionName(const int pId)
{
	if(!mModules)
		return "";

	if(strcmp("ConditionName", mModules->GetString(ColumnNames,RowHeaders)))
	{
		cout << "Object is not a list of Conditions!" << endl;
		return "";
	}

	if(pId < 1 || pId >= getNbModules()-1)
		return "";

	return mModules->GetString(ColumnNames, pId+1); //NOTE: +1 is for Condition 0 should be listed on Row 1
}
*/

