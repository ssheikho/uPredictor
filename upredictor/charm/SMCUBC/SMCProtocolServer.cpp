// SMCProtocolServer.cpp
//


#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>


#include "SMC/SMCProtocolServer.h"
#include "DirectLink/DirectLink.h"
#include <string.h>
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#include <MMSystem.h>
#endif


using namespace SMC;
using namespace std;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : CProtocolServer(const char * pScript, int pVerboseLevel)     //
//                                                                            //
// DESCRIPTION : Constructeur                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

CProtocolServer::CProtocolServer(const char * pScript, int pVerboseLevel /*= 1*/) : 
//   mNbSMCStateTableColumns(0), 
//   mSMCStateTableColumnNames(NULL), 
   mCurrentStep(0),
   mNextStep(1),
//   mNbSMCStates(0),
   mOpen(false),
   mStateTableFilename(NULL), 
   mStateTableData(NULL),
   mStateTableDataSize(0),
   mStateTable(NULL), 
   mStateTableRows(0),
   mStateTableColumns(0),
   mVerboseLevel(pVerboseLevel)
{	
   if (pScript != NULL && *pScript != '\0')
   {
      int lStringLen = strlen(pScript);
      if (lStringLen > 0 && lStringLen < 260)
      {
         mStateTableFilename = new char[lStringLen + 1];
         strcpy(mStateTableFilename, pScript);
      }
   }

   if (mStateTableFilename == NULL)
   {
      const char * lDefaultFileName = "StateTable.csv";
      mStateTableFilename = new char[strlen(lDefaultFileName) + 1];
      strcpy(mStateTableFilename, lDefaultFileName);
   }

   if (pVerboseLevel > 0)
      cout << "SMCProtocolServer: Script filename: \"" << mStateTableFilename << "\"." << endl;


   //DO must initialize SADB stuff
#ifdef __USE_SADB__
   InitSADB();
#endif

   //  mNbModules = CProtocol::InitModules();
   //  mNbConditions = CProtocol::InitConditions();
   //  mNbStates = InitStates();
   CheckLists();

   if (InitStateTable() < 0)
      return;
   //validations
   //unique labels?
   //length <= 20 cars?
   InitSMCPayload();

   mOpen = true;
};


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : ~CProtocolServer()                                           //
//                                                                            //
// DESCRIPTION : Destructeur                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

CProtocolServer::~CProtocolServer()
{
   //free sub level
   if(mStateTable)
   {
      for(int lRow=0; lRow < mStateTableRows; lRow++)
      {
         if(mStateTable[lRow])
            delete [] mStateTable[lRow];

         mStateTable[lRow] = NULL;
      }

      //free table 1
      delete [] mStateTable;
      mStateTable = NULL;
   }

   //Free file memory
   if(mStateTableData)
      delete [] mStateTableData;

   mStateTableData = NULL;
   mStateTableDataSize = 0;

   mStateTableRows = 0;
   mStateTableColumns = 0;

   if (mStateTableFilename != NULL)
   {
      delete mStateTableFilename;
      mStateTableFilename = NULL;
   }

   /*
   if(mSADB)
   {
	   mSADB->Disconnect();
	   delete mSADB;
	   mSADB = NULL;
   }
   */
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : inline bool Match(const char pChar, const char* pCharSet,    //
//               const int pLen=0)                                            //
//                                                                            //
// DESCRIPTION : Match current car to a car from the set (true) pLen argument //
//               is there to explicit handling of strlen() when \0 char is    //
//               part of the pCharSet                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

inline bool Match(const char pChar, const char* pCharSet, const int pLen=0)
{
   unsigned int lLen( (pLen!=0)?(pLen):(strlen(pCharSet)) );

   for(register unsigned int lCar=0; lCar<lLen; lCar++) 
      if(pChar==pCharSet[lCar]) 
         return true;

   return false;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : inline bool NoMatch(const char pChar, const char* pCharSet)  //
//                                                                            //
// DESCRIPTION : same as Match but returns false instead of true;             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

inline bool NoMatch(const char pChar, const char* pCharSet) 
{
	return !Match(pChar, pCharSet);
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int LoadStateTableCSV(const char * pFileName)                //
//                                                                            //
// DESCRIPTION : Load CSV table of states                                     //
//                                                                            //
//               copies all bytes in ram                                      //
//                                                                            //
//               splits it in 2D table of char* (e.g. char*** pointers)       //
//                                                                            //
//               finds first the number of rows and cols                      //
//                                                                            //
//               separate lines by enters composed of \n and/or \r with       //
//               strtok()                                                     //
//                                                                            //
//               separate columns by multiple cases: ,; \t space \n \r        //
//               without strtok() -> colappses multiple separators            //
//                                                                            //
//               removes separator chars before and after isolated keywords   //
//                                                                            //
//               all bytes in ram are at the same place, except separators    //
//               are replaced by \0                                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int CProtocolServer::LoadStateTableCSV(const char *pFileName)
{
   int lSize = 0;

   //Open binary
   FILE* lFile = fopen(pFileName,"rb");
   if(lFile == NULL)
   {
      cerr << "ERROR! Invalid CSV file name=\"" << pFileName << "\"" << endl;
      return -1;
   }

   cout << "CSV file \"" << pFileName << "\" opened" << endl;

   //Finds File size
   struct stat filestatus;
   stat(pFileName, &filestatus);

   if(mVerboseLevel>3)
      cout << "Input FileSize = " << filestatus.st_size << " bytes\n";

   //Alloc memory
   mStateTableData = new char[filestatus.st_size];
   if(mStateTableData==NULL)
      return -2;
   mStateTableDataSize = filestatus.st_size;

   //Read file
   fread(mStateTableData, 1, filestatus.st_size, lFile);
   lSize = mStateTableDataSize;

   //First pass
   for(int lPos=0; lPos<mStateTableDataSize; lPos++)
   {
      if(Match(mStateTableData[lPos], ";,\t",3))
      {
         mStateTableColumns++;

         //check for padding
         if(lPos<mStateTableDataSize-1)
         {
            if(Match(mStateTableData[lPos+1], " \t",2))
               lPos++;
         }

      }
      else
         if(Match(mStateTableData[lPos], "\n\r",2))
         {

            mStateTableRows++;
            mStateTableColumns++;

            //check for extra enter, no line,...
            if(lPos<mStateTableDataSize-1)
            {
               if(Match(mStateTableData[lPos+1], " \n\r\t",4))
                  lPos++;				
            }

         }
   }

   //not the best, but seems to be ok
   mStateTableColumns = mStateTableColumns/mStateTableRows;

   if(mVerboseLevel>3)
      cout << "NbRows="<< mStateTableRows << " NbCols=" << mStateTableColumns << endl;

   //allocate recipient table
   mStateTable = new char**[mStateTableRows];
   for(int lR=0; lR < mStateTableRows; lR++)
      mStateTable[lR] = new char*[mStateTableColumns];

   char * lCurrentRow;
   const char lRowSeparators[] = "\n\r";

   int lRow=0;
   int lCol=0;

   //split lines
   //each line set in 1st col
   lCurrentRow = strtok (mStateTableData, lRowSeparators);
   while (lCurrentRow != NULL && lRow < mStateTableRows)
   {
      mStateTable[lRow][lCol] = lCurrentRow;
      //printf ("%d: %s\n", lRow, lCurrentRow);

      lRow++;
      lCurrentRow = strtok (NULL, lRowSeparators);
   }

   //split columns
   for(lRow=0; lRow<mStateTableRows; lRow++)
   {
      lCol = 0;
      int lLen = strlen(mStateTable[lRow][0]);
      char* lString = mStateTable[lRow][0];
      int i = 0;

      while (lCol < mStateTableColumns && lString != NULL)
      {
         while(!Match(lString[i], ";,\t\n\r\0", 6) )
            i++; 

         lString[i]='\0'; //end of col string

         //pre-clean
         while(Match(mStateTable[lRow][lCol][0]," \t\n\r",3))
         {
            mStateTable[lRow][lCol][0] = '\0';
            ++(mStateTable[lRow][lCol]);
         }

         //post-clean
         int j=strlen(mStateTable[lRow][lCol])-1;
         while(Match(mStateTable[lRow][lCol][j]," \t\n\r",3))
         {
            mStateTable[lRow][lCol][j] = '\0';
            j--;
         }

         if(mVerboseLevel>3)
            printf ("%d,%d=\"%s\" ", lRow, lCol, mStateTable[lRow][lCol]);

         i++; 

         lCol++;
         if(lCol<NbStateTableCols)
            mStateTable[lRow][lCol] = &lString[i]; //next col

         if(i >= lLen)
         {
            for(int lCol2=lCol; lCol2<NbStateTableCols; lCol2++)
               mStateTable[lRow][lCol2] = &lString[lLen];

            lString = NULL; //exit condition
         }

      } //cols

      if(mVerboseLevel>3)
         printf ("\n");

   } //rows

   return lSize;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool CheckStateTable()                                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool CProtocolServer::CheckStateTable()
{
   bool lReturn = true;
   int lErrorCount = 0;
   int lCol=0;

   //check ALL Modules
   lCol = ColDest;
   for(int lRow=1; lRow<mStateTableRows; lRow++)
   {
      tSMCModule lModule = GetModuleId(mStateTable[lRow][lCol]);
      switch(lModule)
      {
         //special cases... when not recognized
      case NONE:
      case UNKNOWN:
         cout << "ERROR: Unrecognized Module name " << mStateTable[lRow][lCol] << " on Row,Col=" << lRow+1 << "," << lCol+1 << endl;
         lErrorCount++;
         lReturn = false;
         break;

      default:
         break;
      }
   }

   //check ALL States names
   lCol = ColState;
   for(int lRow=1; lRow<mStateTableRows; lRow++)
   {
      tSMCState lState = GetStateId(mStateTable[lRow][lCol]);
      switch(lState)
      {
         //special cases... when not recognized
      case STATE_UNKNOWN:
         cout << "ERROR: Unrecognized State name " << mStateTable[lRow][lCol] << " on Row,Col=" << lRow+1 << "," << lCol+1 << endl;
         lErrorCount++;
         lReturn = false;
         break;

      default:
         break;
      }
   }

   //check ALL Conditions / Assignations
   for(int lRow=1; lRow<mStateTableRows; lRow++)
   {
      if(mStateTable[lRow][ColAssignations] && strlen(mStateTable[lRow][ColAssignations])>0)
      {
         cout << "Check assignations on row " << lRow << ":" << endl;
         EvaluateConditions(mStateTable[lRow][ColAssignations]); //there are errors & warnings during parsing
      }
   }

   //we allow empty zones here
   for(lCol = ColSuccess1; lCol<=ColFail; lCol++)
   {
      for(int lRow=1; lRow<mStateTableRows; lRow++)
      {
         if(strlen(mStateTable[lRow][lCol])>0) //something in the column?
         {
            int lCondition = GetConditionId(mStateTable[lRow][lCol]);

            if(lCondition < 0 || lCondition >= GetNbConditions())
            {
               cout << "ERROR: Unrecognized Condition name " << mStateTable[lRow][lCol] << " on Row,Col=" << lRow+1 << "," << lCol+1 << endl;
               lErrorCount++;
               lReturn = false;
            }
         }
         else
         {
            mStateTable[lRow][lCol] = NULL; //replace empty col by NULL string
         }


      }
   }


   //check ALL timeouts

   //Check Description

   //Check connections to next states: Next, Previous,Same, Begin, End Target in column 1
   //lCol = ColNextState; 
   for(int lCas=0; lCas < 2; lCas++, lCol = ((lCas)?ColFailState:ColNextState))
   {
      for(int lRow=1; lRow<mStateTableRows; lRow++)
      {
         if(!strcmp(mStateTable[lRow][lCol], "Next") || strlen(mStateTable[lRow][lCol]) < 1) {}
         else if(!strcmp(mStateTable[lRow][lCol], "Previous")) {}
         else if(!strcmp(mStateTable[lRow][lCol], "Same")) {}
         else if(!strcmp(mStateTable[lRow][lCol], "Begin")) {}
         else if(!strcmp(mStateTable[lRow][lCol], "End")) {}
         else
         {
            //Scan first row for matching item
            int lTargetCol = ColStep;
            bool lFound = false;
            for(int lTargetRow=1; lTargetRow < mStateTableRows; lTargetRow++)
            {
               if(!strcmp(mStateTable[lRow][lCol], mStateTable[lTargetRow][lTargetCol]))
               {
                  lFound = true;
                  break;
               }
            }

            if(lFound)
               break;
            else
            {
               cout << "ERROR: Unrecognized NextStep keyword or name " << mStateTable[lRow][lCol] << " on Row,Col=" << lRow+1 << "," << lCol+1 << endl;
               //cout << "     NOTE: Valid tags are Next,Previous,Same,Begin,End, or whatever is in column " << mStateTable[0][ColStep] << endl;
               lErrorCount++;
               lReturn = false;
            }
         }

      }
   }

   if(lReturn)
      cout << "No errors detected!" << endl;
   else
      cout << "TOTAL NB ERRORS DETECTED: " << lErrorCount << endl;

   return lReturn;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int InitStateTable()                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int CProtocolServer::InitStateTable()
{

   //InitModules();

   //InitConditions();

   //InitStates();
   {
      int lSize = LoadStateTableCSV(mStateTableFilename);
      if (lSize < 0)
      {
         cerr << "Error LoadStateTableCSV" << endl;
         return lSize;
      }

      cout << "CSV file loaded. Size = " << lSize << endl;
   }



   if(!CheckStateTable())
      cout << "Errors found in loaded StateTable!" << endl;

   if(mVerboseLevel>3)
   {
      DumpEnums();

      DumpStateTable();

      //DumpStateTableTranspose();
   }

   return 0;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool CheckLists()                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool CProtocolServer::CheckLists()
{
   int lErrors = 0;
   int lTotalErrors = 0;

   /////////////// modules ///////////////

   lErrors = 0;
   cout << (int)NbSMCModules << " modules available..." << endl;
   for(int lStateId=0; lStateId<(int)NbSMCModules; lStateId++)
      if (!strcmp(GetModuleName(lStateId), "") || GetModuleName(lStateId)==NULL)
      {
         cout << "ERROR: Name for module #"  << lStateId << " is not defined!" << endl;
         lErrors++;
      }

      if(lErrors)
      {
         cout << "Found " << lErrors << " in Module list!" << endl;
         lTotalErrors += lErrors;
      }
      else
         cout << "Module list OK" << endl;
      cout << endl;

      /////////////// states ///////////////

      lErrors = 0;
      cout << (int)CProtocolServer::NbSMCStates << " states available..." << endl;
      for(int lStateId=0; lStateId<(int)CProtocolServer::NbSMCStates; lStateId++) //) is reserved
      {
         if (!strcmp(GetStateName(lStateId), "") || GetStateName(lStateId)==NULL)
         {
            cout << "ERROR: Name for State #"  << lStateId << " not defined!" << endl;
            lErrors++;
         }
      }

      if(lErrors)
      {
         cout << "Found " << lErrors << " in State list!" << endl;
         lTotalErrors += lErrors;
      }
      else
         cout << "State list OK" << endl;

      cout << endl;

      //////////// conditions ///////////////

      lErrors = 0;
      cout << GetNbConditions() << " conditions available..." << endl;
      for(int lCondId=0; lCondId<GetNbConditions(); lCondId++)
         if (!strcmp(GetConditionName(lCondId), "") || GetConditionName(lCondId)==NULL)
         {
            cout << "ERROR: Name for Condition #"  << lCondId << " is not defined!" << endl;
            lErrors++;
         }

         if(lErrors)
         {
            cout << "Found " << lErrors << " in Condition list!" << endl;
            lTotalErrors += lErrors;
         }
         else
            cout << "Condition list OK" << endl;


         cout << endl;
         if(lErrors)
         {
            cout << "Found " << lErrors << " in Condition list!" << endl;
            lTotalErrors += lErrors;
         }

         if(lErrors)
         {
            cout << "Found " << lTotalErrors << " in Condition list!" << endl;
            return true;
         }

         return false;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void InitSMCPayload(tSMCPayload & pSMCPayload)               //
//                                                                            //
// DESCRIPTION : Fills payload with valid / clean data                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CProtocolServer::InitSMCPayload(tSMCPayload &pSMCPayload)
{
   pSMCPayload.Src = CProtocolServer::UNKNOWN;
   pSMCPayload.Dst =  CProtocolServer::UNKNOWN;
   pSMCPayload.Code = ' ';

   for(int lCar=0; lCar<MaxMessageLen; lCar++) //wipe whole Message with 0s
      pSMCPayload.Message[lCar] = '\0';

   pSMCPayload.Step  = 1; //step is the row in the state table, 0 is for the header
   pSMCPayload.State = Begin;

   //clear all condition variables
   for(int lCondId=0; lCondId<NbSMCConditions; lCondId++)
      pSMCPayload.Conditions[lCondId] = eFALSE;

   return;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : CProtocol::tSMCModule ParseModuleName(const char *           //
//               pStrMessage, unsigned int & pPos)                            //
//                                                                            //
// DESCRIPTION : extract Module id starting at pPos in pStrMessage            //
//                                                                            //
//               pPos is modified to point after the extracted keyword        //
//                                                                            //
//               spaces are removed at the beginning of the string            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

CProtocol::tSMCModule CProtocolServer::ParseModuleName(const char * pStrMessage, unsigned int &pPos)
{
   //any number of spaces
   while(Match(pStrMessage[pPos], " "))
      pPos++;

   for(int lIdModule=0; lIdModule<NbSMCModules; lIdModule++)
   {
      //match
      int lLen = strlen(GetModuleName(lIdModule));

      if( !strncmp(&pStrMessage[pPos], GetModuleName(lIdModule), lLen) && Match(pStrMessage[pPos+lLen]," ",1))
      {
         pPos += lLen;
         return (tSMCModule)lIdModule;
         break;
      }
   }

   return NONE;   
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : char ParseCode(const char * pStrMessage, unsigned int &      //
//               pPos)                                                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

char CProtocolServer::ParseCode(const char * pStrMessage, unsigned int &pPos)
{
   char lReturnCode = ' ';

   //remove spaces before
   while(Match(pStrMessage[pPos], " "))
      pPos++;

   //parse code
   switch(pStrMessage[pPos])
   {
   case 'S':
   case 'R':
   case 'F':
      lReturnCode = pStrMessage[pPos];

      if (mVerboseLevel > 1)
         cout << "Code='" << lReturnCode << "'" << endl;

      break;

   default:
      if (mVerboseLevel > 0)
         cout << "Unrecognized code=" << pStrMessage[pPos] << endl;
      lReturnCode = ' '; 
      break;
   }
   pPos += 2;

   return lReturnCode;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : CProtocol::tSMCState ParseStateName(const char* pStrMessage, //
//               unsigned int & pPos)                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

CProtocol::tSMCState CProtocolServer::ParseStateName(const char* pStrMessage, unsigned int &pPos)
{
   //remove any extra spaces (or other chars)
   while(Match(pStrMessage[pPos], " ", 1) && pPos < strlen(mPayload.Message))
      pPos++;

   //parse state label
   for(int lIdState=0; lIdState < NbSMCStates; lIdState++)
   {

      int lLen =  strlen(GetStateName(lIdState));
      //match existing elements

      if(!strncmp( &pStrMessage[pPos], GetStateName(lIdState), lLen) && Match(pStrMessage[pPos+lLen], " =\n\0",4) )
      {
         if (mVerboseLevel > 0)
            cout << "State=" <<  GetStateName(lIdState) << " Id=" << lIdState << endl;

         pPos += lLen;

         return (tSMCState)lIdState;

         break;
      }
   }

   return STATE_UNKNOWN;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool ParseNextCondition(const char* pStrMessage, unsigned    //
//               int & pPos)                                                  //
//                                                                            //
// DESCRIPTION : extract 1 condition from pStrMessage after pPos char         //
//                                                                            //
//               removes any blank space before                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool CProtocolServer::ParseNextCondition(const char* pStrMessage, unsigned int &pPos)
{
   //remove spaces before
   while(Match(pStrMessage[pPos], " \n\r",3))
      pPos++;

   if(pPos>=strlen(pStrMessage))
      return false;

   bool lMatched = false;

   //check all condition names (no space before)
   for(int lIdCond=0; lIdCond<NbSMCConditions; lIdCond++)
   {
      int lLen = strlen(GetConditionName(lIdCond));

      //matched an existing elements
      if(!strncmp( &pStrMessage[pPos], GetConditionName(lIdCond), lLen) && Match(pStrMessage[pPos+lLen], " =!\n\r\0", 6) )
      {
         lMatched = true;

         //if (mVerboseLevel > 0)
         //	cout << "Condition=" <<  mSMCConditionNames[lIdCond] << " Id=" << lIdCond << endl;

         pPos += lLen;

         //if (mVerboseLevel > 1)
         //	cout << "remains=" << &pStrMessage[pPos];

         if(lIdCond<0 || lIdCond>=CProtocol::NbSMCConditions)
            cout << "ERROR BAD CONDITION ID" << endl;

         mPayload.Conditions[lIdCond]  = ParseValue(pStrMessage, pPos);

         if (mVerboseLevel > 0)
            cout << "+ C[" << lIdCond << "]=" << GetConditionName(lIdCond) << "=" << (int)mPayload.Conditions[lIdCond] << endl;

         //abort the search loop
         break; 
      } //if match

   } //for loop

   if(!lMatched)
   {
      cout << "ERROR: did not match \"" << &pStrMessage[pPos] << "\" condition" << endl;

      //skip this one
      while(!Match(pStrMessage[pPos], " \n\r\0", 4))
         pPos++;
   }

   if(pPos < strlen(pStrMessage))
      return true;
   else
      return false;

}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : char ParseValue(const char * pStrMessage, unsigned int &     //
//               pPos)                                                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

char CProtocolServer::ParseValue(const char *pStrMessage, unsigned int &pPos)
{
   char lReturnVal = 0;

   //check if it is followed by '=' (or by 'space' or '\0')
   if(Match(pStrMessage[pPos], " \n\r\0",4) )
      lReturnVal = eTRUE; //implicit true when no value provided (or end of string)
   else
      if(Match(pStrMessage[pPos], "!",1)) //! means NOT or False
      {
         lReturnVal = eFALSE;
         pPos++;
      }
      if(Match(pStrMessage[pPos], "=",1))
      {
         pPos++;

         if(!strncmp(&pStrMessage[pPos], "True", 4) || !strncmp(&pStrMessage[pPos], "true", 4))
         {
            lReturnVal = eTRUE;
            pPos+= 4;
         }
         else
            if(!strncmp(&pStrMessage[pPos], "False", 5) || !strncmp(&pStrMessage[pPos], "false", 5))
            {
               lReturnVal = eFALSE;
               pPos+= 5;
            }
            else
               if(!strncmp(&pStrMessage[pPos], "NULL", 4) || !strncmp(&pStrMessage[pPos], "null", 4))
               {
                  lReturnVal = 0;
                  pPos+= 4;
               }
               else //signed integer values //char value -128..+127 (no decimal part)		
               {				
                  int j=0;
                  char lValue[32] = "";
                  while(Match(pStrMessage[pPos], "+-0123456789"))
                  {
                     lValue[j++]=pStrMessage[pPos++];
                     lValue[j]='\0';
                  }
                  int lIntValue =  atoi(lValue);

                  if(lIntValue >= -128 && lIntValue <= 127)
                     lReturnVal=(char)lIntValue;
                  else
                  {
                     if (mVerboseLevel > 1)
                        cout << "WARNING: Condition value " << lIntValue << " exceeds -128..127 range (signed char)!" << endl;
                  }
               }

      } //match

      return lReturnVal;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool ParseMessage(const char* pStrMessage)                   //
//                                                                            //
// DESCRIPTION : method called to parse messages sent by clients              //
//                                                                            //
//               return 0 for empty strings / null strings                    //
//                                                                            //
//               return lPos of last passed byte (some attribute/comment may  //
//               remain available at that lPos in string)                     //
//                                                                            //
//               DO modified for v2.0:                                        //
//                                                                            //
//               1)multiple attributes with true, True, false, False, null,   //
//               NULL and char values                                         //
//                                                                            //
//               2) elements separated by space                               //
//                                                                            //
//               3) assignation of values with = between label and value (no  //
//               space)                                                       //
//                                                                            //
//               3)attribute =true or 1 by default                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool CProtocolServer::ParseMessage(const char* pStrMessage)
{
   unsigned int lPos = 0;

   if (mVerboseLevel > 1)
      cout << "Msg=<<" << pStrMessage << ">>" << endl;

   //message should be filled by SMC itself (not by parse)

   //default outputs
   mPayload.Src = CProtocolServer::UNKNOWN;
   mPayload.Dst =  CProtocolServer::UNKNOWN;
   mPayload.Code = ' ';
   //mPayload.Step = 0;

   //no string (do nothing)
   if(pStrMessage==NULL)
   {
      if (mVerboseLevel > 1)
         cout << "Null string" << endl;
      return 0;
   }

   //case of empty message (do nothing)
   if(pStrMessage[0]==0)
   {
      if (mVerboseLevel > 1)
         cout << "Empty string" << endl;
      return 0;
   }

   //parse Src
   mPayload.Src = ParseModuleName(pStrMessage, lPos);

   //parse Dst
   mPayload.Dst = ParseModuleName(pStrMessage, lPos);

   if (mVerboseLevel > 1)
   {
      cout << "Src=" << (int)mPayload.Src << ":" << GetModuleName(mPayload.Src) << endl;
      cout << "Dst=" << (int)mPayload.Dst << ":" << GetModuleName(mPayload.Dst) << endl;
   }

   mPayload.Code = ParseCode(pStrMessage, lPos);

   if (mPayload.Code == 'S')
   {
      mPayload.State = ParseStateName(pStrMessage, lPos);
   }
   else
      if(mPayload.Code == 'R' || mPayload.Code == 'F')
         ParseNextCondition(pStrMessage, lPos);

   //other
   //copy message... <= MaxMessageLen
   strncpy(mPayload.Message, pStrMessage, MaxMessageLen);
   mPayload.Message[MaxMessageLen-1] = '\0'; //safety to prevent longer messages

   //we still have lPos to help continue parsing of the attributes
   if (mVerboseLevel > 1)
   {
      cout << "lPos = " << lPos << endl; 
      cout << "MessageEnd = <<" << &pStrMessage[lPos] << ">>" <<endl;
   }

   //more attributes...
   //this is what is left after the labels (end of message)

   //after 1 condition or state message, we allow more attributes
   //parse other parameters form {condition1=value1{space}}
   while(lPos < strlen(mPayload.Message))
   {
      if(!ParseNextCondition(pStrMessage, lPos))
         break;

   } // all conditions

   //OPTIONAL: not sure if useful here...
   //remove any extra spaces (or other chars)
   while(Match(pStrMessage[lPos], " ") && lPos < strlen(mPayload.Message))
      lPos++;

   return (lPos>1); 
}

//=====================================================
#ifdef _TOTO_
//we use a state table to evaluate current, next, fail state from conditions
//AllOk = true is mandatory before changing state
bool CProtocolServer::OldEvaluateState()
{
   //column IDs for table
   enum columnID {eModuleID, eActualStateID, eNextStateID, eFailStateID, ePrimCondID, eSecCondID, eFailCondID, eRepeatTimeout, eMaxMatrixColumns};


   //Global State Transition Table
   //columns
   //0: module id
   //1: actual state
   //2: next state  (-1 or NextState means next state in list)
   //3: fail safe state (if a Failure happens during this state)
   //4: 1st condition (anded)   -1 means not used (but we need one condition)
   //5: 2nd condition (anded)   -1 means not used
   //6: fail condition          -1 means not used

   //Not used yet Removed to evoid a Warning in Linux: static double lStateBeginTime = 0.0;

   static const int lStateMatrix[MaxNbSMCStates][eMaxMatrixColumns] = {
      {ALL, Begin            , NextState         , Finish    , AllOk             , -1 ,  -1, 60}, //just load modules
      {T3O, InitT3O          , NextState         , Finish    , T3OReady          , -1 ,  -1, 0},
      {T3W, InitT3W          , NextState         , FinishT3O , T3WReady          , -1 ,  T3WFailed, 0}, //T3WReady, T3WFailed
      {T3P, InitT3P          , NextState         , FinishT3W , T3PReady          , -1 ,  -1, 0}, 
      {T2 , InitT2           , NextState         , FinishT3P , T2Ready           , -1 ,  -1, 0},
      {T1 , InitT1           , NextState         , T2Finish  , T1Ready           , -1 ,   T1Failed, 0 }, //Inits completed

      {T3W, CheckWorker      , NextState         , FinishT1  , WorkerPresent     , -1 ,   -1 , 10}, //  T3WInProgress, WorkerPresent, T3WFailed

      {T3P, CheckParts       , NextState         , FinishT1  , PartOnTray        , -1 ,   -1 , 10}, //T3PInProgress, PartOnTray
      {T3O, CheckFreeSpaceD  , NextState         , FinishT1  , FreeSpaceToDeliver, -1 ,   -1 , 10}, //goto worker
      {T2 , T2GotoDelivery   , NextState         , FinishT1  , T2MoveComplete    , -1 ,   -1 , 0},
      {T1 , T1DeliverPart    , NextState         , FinishT1  , T1Done            , PartTaken ,   T1Failed, 0}, //Deliver part (super state)

      //sub states:
      //1)x WaitingForWorker		  -> T3W SMC R WorkerPresent
      //2) PresentingPart		     -> T1  SMC R PresentingPart


      //3) WaitingForPickup		  -> T3P SMC R PartTaken
      //PartPickedUp	(event)		  -> T1  SMC R PartPickedUp

      {T1 , T1RetractTray    , NextState         , FinishT1  , TrayRetracted     , -1 ,   T1Failed, 0}, //Tray retract (added DO + Amir)

      //4) RetractingTray			  -> T1  SMC R RetractingTray
      //TrayRetracted (event)	 	  -> T1  SMC R TrayRetracted
      //T1Done	 (event) - final response	(normal)		  
      //T1Failed (event)	- final report (failure)		   

      {T3O, CheckFreeSpaceS  , NextState         , FinishT1  , FreeSpaceToSupply, -1,   -1 , 10}, //return to supply
      {T2 , T2GotoSupply     , NextState         , FinishT1  , T2MoveComplete,    -1,   -1 , 0},
      {ALL, Iterate          , CheckWorker       , FinishT1  , NextPart,          -1,   AssemblyComplete, 0}, //iterate: check with T3 if assembly is completed or not

      {T1 , FinishT1         , NextState         , T2Finish  , T1Done,            -1,   T1Failed, 0 },  //Task complete, start cleanup
      {T2 , T2Finish         , NextState         , FinishT3P , T2Done,            -1,   -1, 0},
      {T3P, FinishT3P        , NextState         , FinishT3W , T3PReady,          -1,   -1, 0}, //T3PInProgress, T3PReady
      {T3W, FinishT3W        , NextState         , FinishT3O , T3WReady,          -1,   -1, 0},
      {T3O, FinishT3O        , NextState         , Finish    , T3OReady,          -1,   -1, 0},
      {ALL, Finish           , Begin             , Begin     , -1,                -1,   -1, 0}      //go back to init (maybe we have Restart and Quit)
   }; 

   tSMCState lCurrentState = mPayload.State;
   tSMCState lNextState = lCurrentState;

   //need row index, since state names do not have same enum index.
   //row sequence is important
   int lCurrentRow = 0; //default to Begin
   int lNextRow = 0; 

   //check AllOk
   if(mPayload.Conditions[AllOk]==eFALSE)
      return false;

   //locate current row... (full traversal / unique names)

   for(int lStateId=0; lStateId<MaxNbSMCStates; lStateId++)
   {
      if(lStateMatrix[lStateId][eActualStateID]==lCurrentState)
      {
         lCurrentRow = lStateId;
         if (mVerboseLevel > 0)
            cout << "found actual state "<< mSMCStateNames[lCurrentState] <<" on row " << lStateId << endl;
         break;
      }
   }

   //Not used yet double. Removed to evoid a Warning in Linux: lTimeout = (double)lStateMatrix[lCurrentRow][eRepeatTimeout];

   //evaluate the conditions
   bool lChangeState = true;

   if(lStateMatrix[lCurrentRow][ePrimCondID]!=-1 && mPayload.Conditions[ lStateMatrix[lCurrentRow][ePrimCondID] ]!=eTRUE)
   {
      lChangeState = false;
      //if (mVerboseLevel > 0)
      if(lStateMatrix[lCurrentRow][ePrimCondID] != -1)
         cout << "  * primary condition " << mSMCConditionNames[ lStateMatrix[lCurrentRow][ePrimCondID] ] << " not met." << endl;
   }

   if(lStateMatrix[lCurrentRow][eSecCondID]!=-1 && mPayload.Conditions[ lStateMatrix[lCurrentRow][eSecCondID] ]!=eTRUE)
   {
      lChangeState = false;
      //if (mVerboseLevel > 0)
      if(lStateMatrix[lCurrentRow][eSecCondID] != -1)
         cout << "  * secondary condition " <<  mSMCConditionNames[ lStateMatrix[lCurrentRow][eSecCondID] ] << " not met." << endl;
   }

   if(lChangeState) 
   {
      if (mVerboseLevel > 0)
         cout << "SMC state change condition met." << endl;

      //take the one specified if not -1
      if(lStateMatrix[lCurrentRow][eNextStateID] >=0)
      {
         lNextState = (tSMCState)lStateMatrix[lCurrentRow][eNextStateID];
         if (mVerboseLevel > 0)
            cout << "SMC going to next state = " << mSMCStateNames[lNextState] << endl;
      }
      else //take the next one, if not at the end of the state machine
         if(lCurrentRow<MaxNbSMCStates-1)
         {
            lNextState = (tSMCState)lStateMatrix[lCurrentRow+1][eActualStateID];
            if (mVerboseLevel > 0)
               cout << "SMC going to default next state = " << mSMCStateNames[lNextState] << endl;
         }
         else //take row 0 otherwise (Finish->Begin)
         {
            lNextState = (tSMCState)lStateMatrix[0][eActualStateID];
            if (mVerboseLevel > 0)
               cout << "SMC going to default initial state = " << mSMCStateNames[lNextState] << endl;
         }
   }
   else  //Check failure condition
      if(lStateMatrix[lCurrentRow][eFailCondID]>=0 && mPayload.Conditions[lStateMatrix[lCurrentRow][eFailCondID]]==eTRUE)
      {
         if (mVerboseLevel > 0)
            cout << "SMC fail state condition " << mSMCConditionNames[ lStateMatrix[lCurrentRow][eFailCondID] ] << " met." << endl;

         if(lStateMatrix[lCurrentRow][eFailStateID] >=0)
         {
            lNextState = (tSMCState)lStateMatrix[lCurrentRow][eFailStateID];
            if (mVerboseLevel > 0)
               cout << "SMC going to failure state = " << mSMCStateNames[lNextState] << endl;
         }
      }   

      if(lNextState != lCurrentState)
      {
         //find my next row corresponding to next state
         lNextRow = 0;
         for(int i=0; i<MaxNbSMCStates; i++)
         {
            if(lStateMatrix[i][eActualStateID]==lNextState)
            {
               lNextRow = i;
               if (mVerboseLevel > 0)
                  cout << "found actual state "<< mSMCStateNames[lNextState] <<" on row " << i << endl;
               break;
            }
         }

         //reset conditions before passing to the next state (require responses from clients)

         //must reset conditions required for next state exit
         if(lStateMatrix[lNextRow][ePrimCondID]!=-1)
            mPayload.Conditions[lStateMatrix[lNextRow][ePrimCondID]]=eFALSE;

         if(lStateMatrix[lNextRow][eSecCondID]!=-1)
            mPayload.Conditions[lStateMatrix[lNextRow][eSecCondID]]=eFALSE;

         //must reset conditions required for failure exit
         if(lStateMatrix[lNextRow][eFailCondID]!=-1)
            mPayload.Conditions[lStateMatrix[lNextRow][eFailCondID]]=eFALSE;       

         //set my binary format (enums)
         mPayload.Src = SMC;
         mPayload.Dst = (tSMCModule)lStateMatrix[lNextRow][eModuleID];
         mPayload.State = lNextState;

         //lStateBeginTime = getTime();

         switch(lCurrentState)
         {         
         case Begin:
         case InitT1:
         case InitT3P:
            mPayload.Conditions[CProtocol::PartCount] = 0; //mPayload.PartCount = 0;
            mPayload.Conditions[NextPart] = eFALSE;
            mPayload.Conditions[AssemblyComplete] = eFALSE;
            break;

         case CheckWorker: //1st state after iterate
            mPayload.Conditions[NextPart] = eFALSE;
            mPayload.Conditions[AssemblyComplete] = eFALSE;  
            mPayload.Conditions[T1Done] = eFALSE;
            mPayload.Conditions[T2MoveComplete] = eFALSE;
            mPayload.Conditions[FreeSpaceToDeliver] = eFALSE;
            mPayload.Conditions[FreeSpaceToSupply] = eFALSE;
            mPayload.Conditions[PartOnTray] = eFALSE;
            mPayload.Conditions[PartTaken] = eFALSE;
            mPayload.Conditions[PartInPlace] = eFALSE;
            break;


         case Iterate: //Special case with Iterate -> update+1 PartCounter
            mPayload.Conditions[CProtocol::PartCount]++;
            if (mVerboseLevel > 0)
               cout << "Update PartCounter=" << (int)mPayload.Conditions[CProtocol::PartCount] << endl;
            break;

            //we wait for AssemblyComplete or NextPart (I'll let T3P respond with these conditions) 

         default:
            break;
         }


         //generate corresponding text message
         sprintf(mPayload.Message, "%s%sS %s", mSMCModuleNames[mPayload.Src], mSMCModuleNames[mPayload.Dst], mSMCStateNames[ mPayload.State]);
         //if (mVerboseLevel > 1)
         cout << "Message=<<" << mPayload.Message << ">>" << endl; 
      }
      else
      {
         if (mVerboseLevel > 1)
            cout << "Empty Message" << endl; 

         //clear message variables
         mPayload.Src = SMC;
         mPayload.Dst = ALL;
         mPayload.Code = 'R';
         mPayload.Message[0] = '\0';
      }

      return (lCurrentState != lNextState);
}

#endif //__TOTO__


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int FindStep(const int pCurrentStep, const char* pStepName)  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int CProtocolServer::FindStep(const int pCurrentStep,  const char* pStepName)
{
   int lNextStep = pCurrentStep;	

   if((pStepName==NULL) || !strcmp(pStepName, "Next") || !strcmp(pStepName, ""))
   {
      lNextStep++;
      while(!strcmp(mStateTable[lNextStep][ColStep], "") && lNextStep<mStateTableRows) //skip empty step names
         lNextStep++;
   }
   else
      if(!strcmp(pStepName, "Previous"))
      {
         lNextStep--;
         while(((mStateTable[lNextStep][ColStep]==NULL) || !strcmp(mStateTable[lNextStep][ColStep], "")) && lNextStep>1) //skip empty step names
            lNextStep--;
      }
      else
         if(!strcmp(pStepName, "Same"))
         {
            //do nothing
         }
         else
            if(!strcmp(pStepName, "Begin") || !strcmp(pStepName, "End"))
            {
               //Search End or Begin in State columns

               for(int i=0; i<mStateTableRows; i++)
               {
                  int lRow = (pCurrentStep+i)%mStateTableRows;

                  if(lRow==0)
                     continue;

                  if(!strcmp(pStepName, mStateTable[lRow][ColState]))
                     lNextStep = lRow;
               }
            }
            else
            {
               //search
               for(int i=0; i<mStateTableRows; i++)
               {
                  int lRow = (pCurrentStep+i)%mStateTableRows;

                  if(lRow==0)
                     continue;

                  if(!strcmp(pStepName, mStateTable[lRow][ColStep]))
                     lNextStep = lRow;

               }
            }

            return lNextStep;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : bool EvaluateState()                                         //
//                                                                            //
// DESCRIPTION : we use a state table to evaluate current, next, fail state   //
//               from conditions                                              //
//                                                                            //
//               AllOk = true is mandatory before changing state              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

bool CProtocolServer::EvaluateState()
{
   static double lStateBeginTime = 0.0; //used for timeout computation
   bool lTimeout = false; //indicate when timeout happens

   tSMCState lCurrentState = mPayload.State;
   //tSMCState lNextState    = lCurrentState;

   //we use step (row number) to track what is being done
   //state are not unique this time
   //int       mCurrentStep  = mStep; //mPayload.Step;
   //int       mNextStep = 1; 

   //evaluate the conditions
   bool lChangeState = true;

   //check AllOk
   if(mPayload.Conditions[AllOk]==eFALSE)
      return false;

   //locate current row... (full traversal / unique names)
   if(mCurrentStep<1 || mCurrentStep>= mStateTableRows)
   {
      //search Begin
      for(int lRow=0; lRow<mStateTableRows; lRow++)
      {
         if(!strcmp(mStateTable[lRow][ColState], "Begin"))
         {
            mCurrentStep = lRow;
            mNextStep = lRow;
            mPayload.Step = lRow;
         }
      }

      //init begin time
      lStateBeginTime = DirectLink::CDirectLink::getTime();

      //lTimeout = true;
      //assignations associated with Begin state
      if(mStateTable[mCurrentStep][ColAssignations] && strlen(mStateTable[mCurrentStep][ColAssignations])>0)
         EvaluateConditions(mStateTable[mCurrentStep][ColAssignations]);

      return false;

   }
   else
   {
      for(int i=0; i<mStateTableRows; i++)
      {
         int lRow = (mCurrentStep+i)%mStateTableRows;

         if(lRow==0) //skip 1st row w headers
            lRow++;

         if(lCurrentState==GetStateId(mStateTable[lRow][ColState]))
         {
            mCurrentStep = lRow;
            if (mVerboseLevel > 0)
               cout << "found actual state "<< GetStateName(lCurrentState) <<" on row " << lRow << endl;
            break;
         }
      }
   }

   //Not used yet double. Removed to avoid a Warning in Linux: lTimeout = (double)lStateMatrix[lCurrentRow][eRepeatTimeout];

   lChangeState = true;
   //Success1
   if(mStateTable[mCurrentStep][ColSuccess1])
   {
      if(mPayload.Conditions[ GetConditionId(mStateTable[mCurrentStep][ColSuccess1]) ]==0)
      {
         lChangeState = false;
         cout << "  * SC1 " << mStateTable[mCurrentStep][ColSuccess1] << " not met." << endl;
      }
      else
         cout << "  * SC1 " << mStateTable[mCurrentStep][ColSuccess1] << " OK" << endl;
   }


   //Success2
   if(mStateTable[mCurrentStep][ColSuccess2])
   {
      if(mPayload.Conditions[ GetConditionId(mStateTable[mCurrentStep][ColSuccess2]) ]==0)
      {
         lChangeState = false;
         cout << "  * SC2 " << mStateTable[mCurrentStep][ColSuccess2] << " not met." << endl;
      }
      else
         cout << "  * SC2 " << mStateTable[mCurrentStep][ColSuccess2] << " OK" << endl;
   }

   //Success3
   if(mStateTable[mCurrentStep][ColSuccess3])
   {
      if(mPayload.Conditions[ GetConditionId(mStateTable[mCurrentStep][ColSuccess3]) ]==0)
      {
         lChangeState = false;
         cout << "  * SC3 " << mStateTable[mCurrentStep][ColSuccess3] << " not met." << endl;
      }
      else
         cout << "  * SC3 " << mStateTable[mCurrentStep][ColSuccess3] << " OK" << endl;
   }


   cout << endl;

   //determine timeout
   double lTimeoutSecs = 0.0;
   if(mStateTable[mCurrentStep][ColTimeout] && strlen(mStateTable[mCurrentStep][ColTimeout])>0 )
      lTimeoutSecs = atof(mStateTable[mCurrentStep][ColTimeout]); 

   double lStateDuration = DirectLink::CDirectLink::getTime(lStateBeginTime);

   cout << "StateDuration = " << lStateDuration << " / " << lTimeoutSecs << endl;

   //timeout val when no condition available
   if(!mStateTable[mCurrentStep][ColSuccess1] && !mStateTable[mCurrentStep][ColSuccess3] && !mStateTable[mCurrentStep][ColSuccess3])
   {
      if(lStateDuration > lTimeoutSecs)
         lTimeout = true; //same as a successful state
      else
      {
         lTimeout = false;

         if(mVerboseLevel > 1)
            cout << "timeout condition not met..." << endl;

         return false; //change nothing
      }
   }

   if(lChangeState) //N conditions are met
   {
      if (mVerboseLevel > 0)
         cout << "SMC state change condition met." << endl;

      if (mVerboseLevel > 0)
         cout << "CurrentStep=" << mStateTable[mCurrentStep][ColStep] << endl;


      if(mStateTable[mCurrentStep][ColSound] && strcmp(mStateTable[mCurrentStep][ColSound],""))
         PlaySMCSound(mStateTable[mCurrentStep][ColSound]);

      //take the one specified if not -1
      if(mStateTable[mCurrentStep][ColNextState] && strlen(mStateTable[mCurrentStep][ColNextState])>0 )
      {
         mNextStep = FindStep(mCurrentStep, mStateTable[mCurrentStep][ColNextState]);
         if (mVerboseLevel > 0)
            cout << mStateTable[mCurrentStep][ColStep] << ": next state=" << mStateTable[mCurrentStep][ColNextState] << " Solved= " << mStateTable[mNextStep][ColStep] << endl;
      }
      else //take the next one, if not at the end of the state machine
         if(mCurrentStep < mStateTableRows-1)
         {
            mNextStep = FindStep(mCurrentStep, "Next");
            if (mVerboseLevel > 0)
               cout << "SMC going to default next state=" << mStateTable[mNextStep][ColStep] << " State="<< mStateTable[mNextStep][ColState] << endl;
         }
         else //take row 0 otherwise (Finish->Begin)
         {
            mNextStep = FindStep(mCurrentStep, "Begin");
            if (mVerboseLevel > 0)
               cout << "SMC going to default initial state=" << mStateTable[mNextStep][ColStep] << "State="<< mStateTable[mNextStep][ColState] << endl;
         }

         if (mVerboseLevel > 0)
            cout << "NextStep=" << mStateTable[mNextStep][ColStep] << endl;
   }
   else  //Check failure condition
      if(mStateTable[mCurrentStep][ColFail] && mPayload.Conditions[ GetConditionId(mStateTable[mCurrentStep][ColFail]) ]!=0)
      {
         lChangeState = false;
         if(mStateTable[mCurrentStep][ColFail])
            cout << "SMC going to failure state = " << mStateTable[mCurrentStep][ColFailState] << endl;

         //Search next step
         //lNextState =
         mNextStep = FindStep(mCurrentStep,  mStateTable[mCurrentStep][ColFailState]);
      }
      else
      {
         lStateDuration = DirectLink::CDirectLink::getTime(lStateBeginTime);
         if(lStateDuration > lTimeoutSecs)
         {
            cout << "Timeout condition met." << endl;
            lTimeout = true;
            mNextStep = mCurrentStep;
         }
         else
            lTimeout = false;

      }

      //Processing to "New" step

      if(mNextStep != mCurrentStep || lTimeout)
      {

         //reset conditions before passing to the next state (require responses from clients)
         //must reset conditions required for next state exit

         //3 success conditions
         if(mStateTable[mNextStep][ColSuccess1] && strlen(mStateTable[mNextStep][ColSuccess1])>0)
            mPayload.Conditions[GetConditionId(mStateTable[mNextStep][ColSuccess1])]=0;

         if(mStateTable[mNextStep][ColSuccess2] && strlen(mStateTable[mNextStep][ColSuccess2])>0)
            mPayload.Conditions[GetConditionId(mStateTable[mNextStep][ColSuccess2])]=0;

         if(mStateTable[mNextStep][ColSuccess3] && strlen(mStateTable[mNextStep][ColSuccess3])>0)
            mPayload.Conditions[GetConditionId(mStateTable[mNextStep][ColSuccess3])]=0;

         //1 fail condition
         if(mStateTable[mNextStep][ColFail] && strlen(mStateTable[mNextStep][ColFail])>0)
            mPayload.Conditions[GetConditionId(mStateTable[mNextStep][ColFail])]=0; 

         //set my binary format (enums)
         mPayload.Src = SMC;
         mPayload.Dst = GetModuleId(mStateTable[mNextStep][ColDest]);
         mPayload.State = GetStateId(mStateTable[mNextStep][ColState]);
         mPayload.Step  = mNextStep;

         lStateBeginTime = DirectLink::CDirectLink::getTime();

         //Implicit inits
         switch(lCurrentState)
         {         
         case Begin:

            mPayload.Conditions[SMCReady] = eTRUE;

            //PLS USE EXPLICIT INITS

            //for(int i=0; i<NbSMCConditions; i++)
            //	mPayload.Conditions[i]=0;
            break;

            /*
            case InitT1:
            case InitT3P:
            //mPayload.Conditions[CProtocol::PartCount] = 0; //mPayload.PartCount = 0;
            mPayload.Conditions[NextPart] = eFALSE;
            mPayload.Conditions[AssemblyComplete] = eFALSE;
            break;
            */

            /*
            case CheckWorker: //1st state after iterate
            mPayload.Conditions[NextPart] = eFALSE;
            mPayload.Conditions[AssemblyComplete] = eFALSE;  
            mPayload.Conditions[T1Done] = eFALSE;
            mPayload.Conditions[T2MoveComplete] = eFALSE;
            mPayload.Conditions[FreeSpaceToDeliver] = eFALSE;
            mPayload.Conditions[FreeSpaceToSupply] = eFALSE;
            mPayload.Conditions[PartOnTray] = eFALSE;
            mPayload.Conditions[PartTaken] = eFALSE;
            mPayload.Conditions[PartInPlace] = eFALSE;
            break;
            */

         case Iterate: //Special case with Iterate -> update+1 PartCounter
            mPayload.Conditions[CProtocol::PartCount]++;

            if (mVerboseLevel > 0)
               cout << "Update PartCounter=" << (int)mPayload.Conditions[CProtocol::PartCount] << endl;

            break;

            //we wait for AssemblyComplete or NextPart (I'll let T3P respond with these conditions) 

         case Finish:
            break;

         default:
            break;
         }

         //explicit conditions

         int lNbVars = EvaluateConditions(mStateTable[mPayload.Step][ColAssignations]);

         if (mVerboseLevel > 1 && lNbVars > 0)
         {
            cout << "Assign" << lNbVars << " variables from\"" << mStateTable[mPayload.Step][ColAssignations] << "\"" << endl;
         }


         //generate corresponding text message
         //UPDATE: added spaces (one or more required), 
         //        no max name length for Modules, States, multiple Conditions,... 
         //        no mandatory \n at the end but works with it too
         int lLen = sprintf(mPayload.Message, "%s %s S %s Step=%s %s", GetModuleName(mPayload.Src), GetModuleName(mPayload.Dst), GetStateName(mPayload.State), mStateTable[mCurrentStep][ColStep], mStateTable[mPayload.Step][ColAssignations]);

         if(lLen >= MaxMessageLen)
         {
            cout << "ERROR: Message too long! Len=" << lLen << " >= " << MaxMessageLen  << " max" << endl;
         }

         if (mVerboseLevel > 1)
            cout << "Message=<<" << mPayload.Message << ">>" << endl; 
      }
      else
      {
         if (mVerboseLevel > 1)
            cout << "Empty Message" << endl; 

         //clear message variables
         mPayload.Src = SMC;
         mPayload.Dst = ALL;
         mPayload.Code = 'R';
         mPayload.Step = mCurrentStep;
         mPayload.Message[0] = '\0';
      }

      //return (lCurrentState != lNextState || lTimeout || lChangeState);
      return lChangeState;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int EvaluateConditions(const char* pInputString)             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int CProtocolServer::EvaluateConditions(const char* pInputString)
{
   int lNbVars = 0;

   unsigned int lPos = 0;

   while(ParseNextCondition(pInputString, lPos))
   {
      lNbVars++;
      if (mVerboseLevel > 1)
         cout << "#" << lNbVars << " remains \"" << &pInputString[lPos] << "\"" << endl;
   }

   return lNbVars;
}


//=====================================================


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void OldDumpEnums()                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CProtocolServer::OldDumpEnums()
{
   cout << (int)NbSMCModules << " modules available..." << endl;
   for(int i=0; i<(int)NbSMCModules; i++)
      cout << i << ":" << GetModuleName(i) << endl;
   cout << endl;

   cout << (int)CProtocolServer::NbSMCStates << " states available..." << endl;
   for(int i=0; i<(int)CProtocolServer::NbSMCStates; i++)
      cout << i << ":" << CProtocolServer::GetStateName(i) << endl;
   cout << endl;

   cout << (int)NbSMCConditions << " conditions available..." << endl;
   for(int i=0; i<(int)NbSMCConditions; i++)
      cout << i << ":" << GetConditionName(i) << endl;
   cout << endl;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void DumpEnums()                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CProtocolServer::DumpEnums()
{
   cout << (int)NbSMCModules << " modules available..." << endl;
   for(int i=0; i<(int)NbSMCModules; i++)
   {
      cout << i << ":" << GetModuleName(i);
      if(IsMandatoryModule(i))
         cout << " Mandatory";
      cout << endl;
   }
   cout << endl;

   cout << (int)CProtocolServer::NbSMCStates << " states available..." << endl;
   for(int i=0; i<(int)CProtocolServer::NbSMCStates; i++)
      cout << i << ":" << GetStateName(i) << endl;
   cout << endl;

   cout << (int)NbSMCConditions << " conditions available..." << endl;
   for(int i=0; i<(int)NbSMCConditions; i++)
      cout << i << ":" << GetConditionName(i) << endl;

   cout << endl;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void DumpStateTable()                                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CProtocolServer::DumpStateTable()
{
   register int lRow = 0;
   register int lCol = 0;

   printf("StateTable (row by row):\n");

   for(lRow=0; lRow<mStateTableRows; lRow++)
   {
      if(mVerboseLevel>1) 
         printf("(%02d)", lRow);

      for(lCol=0; lCol<mStateTableColumns; lCol++)
      {
         if(mStateTable[lRow][lCol]!=NULL)
            printf("%s;", mStateTable[lRow][lCol]);
         else
            printf(";");
      }
      //printf("%s\n", mStateTable[lRow][lCol]);

      //if(mVerboseLevel>1) 
      printf("\n\n");
   }


}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : void DumpStateTableTranspose()                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void CProtocolServer::DumpStateTableTranspose()
{
   register int lRow = 0;
   register int lCol = 0;

   printf("StateTable (organized by columns...)\n");

   for(lCol=0; lCol<mStateTableColumns; lCol++)
   {
      //if(mVerboseLevel>1) 
      //	printf("(%02d)", lRow);

      for(lRow=0; lRow<mStateTableRows; lRow++)
      {
         if(mStateTable[lRow][lCol]!=NULL)
            printf("%s;", mStateTable[lRow][lCol]);
      }
      //printf("%s\n", mStateTable[lRow][lCol]);

      //if(mVerboseLevel>1) 
      printf("\n\n");
   }
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// METHOD      : int PlaySMCSound(const char* pSoundName)                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int SMC::CProtocolServer::PlaySMCSound(const char* pSoundName)
{
   string lFileName = pSoundName;

   lFileName.append(".wav");

#ifdef WIN32
   cout << " Sound file " << lFileName << " will eventually be played..." << endl;
   PlaySound(lFileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);
#else
   cout << " No sound on linux presently the file \"" << lFileName << "\" will no be played." << endl;
#endif

   return 0;
}
//end of protocol.cpp

const char* SMC::CProtocolServer::GetTableColumnName(const int pId)
{
	switch(pId)
	{
	case SMC::CProtocolServer::ColStep:		return "ColStep";
	case SMC::CProtocolServer::ColDesc:		return "ColDesc";
	case SMC::CProtocolServer::ColState:	return "ColState";
	case SMC::CProtocolServer::ColDest:		return "ColDest";
	case SMC::CProtocolServer::ColNextState: return "ColNextState";
	case SMC::CProtocolServer::ColSuccess1: return "ColSuccess1";
	case SMC::CProtocolServer::ColSuccess2: return "ColSuccess2";
	case SMC::CProtocolServer::ColSuccess3: return "ColSuccess3";
	case SMC::CProtocolServer::ColFail:		return "ColFail";
	case SMC::CProtocolServer::ColFailState: return "ColFailState";
	case SMC::CProtocolServer::ColTimeout:	return "ColTimeout";
	case SMC::CProtocolServer::ColAssignations: return "ColAssignations";
	case SMC::CProtocolServer::ColSound:	return "ColSound";

	//failures and unknown cases
	case SMC::CProtocolServer::NbStateTableCols: 
		return "";
	
	default: 
		return "";
	}
}

const int SMC::CProtocolServer::GetTableColumnId(const char* pName)
{
	for(int iColId=0; iColId<SMC::CProtocolServer::NbStateTableCols; iColId++)
		if(!strcmp(GetTableColumnName(iColId), pName))
			return iColId;
	//Failure
	return 0;
}