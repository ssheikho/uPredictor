//SMCProtocolServer.h

#ifndef _SMC_PROTOCOL_SERVER_H_
#define _SMC_PROTOCOL_SERVER_H_ 

//#include "SADBClient.h"

#include <iostream>
#include "SMCProtocol.h"

namespace SMC {

   class CProtocolServer: public CProtocol
   {
   public:
      ////////////////////////////
      ////// Public Methods //////
      ////////////////////////////
      CProtocolServer (const char *pScript, int pVerboseLevel = 1);
      ~CProtocolServer();

      //arrays for labels 
      //char* mSMCModuleNames[NbSMCModules];
      //const char* mSMCStateNames[MaxNbSMCStates];
      //char* mSMCConditionNames[(const int)NbSMCConditions];

      inline void InitSMCPayload() {InitSMCPayload(mPayload);}
      static void InitSMCPayload(tSMCPayload &pSMCPayload);

      bool ParseMessage(const char* pStrMessage);
      bool OldEvaluateState();
      bool EvaluateState();

      void OldDumpEnums();
      void DumpEnums();

      void DumpStateTable();
      void DumpStateTableTranspose();

      inline bool IsOpen() const {return mOpen;}

      //inline void SetCondition(int pConditionId, char pState=1) {pState ? mPayload.Conditions[pConditionId]=pState : mPayload.Conditions[pConditionId]=0;};
      inline void SetCondition(int pConditionId, char pState) {if(pConditionId>=0 && pConditionId<GetNbConditions()) mPayload.Conditions[pConditionId]=pState;};
      inline void SetCondition(const char* pConditionName, char pState) { int pConditionId = GetConditionId(pConditionName); if(pConditionId>=0 && pConditionId<NbSMCConditions) mPayload.Conditions[pConditionId]=pState;};
      inline void ResetCondition(int pCondition) {SetCondition(pCondition, 0);}
      inline void ResetCondition(const char* pConditionName) {int pConditionId = GetConditionId(pConditionName); SetCondition(pConditionId, 0);}

      //ADD ByName calls / standard is by Id
      //ADD GetConditionIdByName
      inline const int GetConditionId(const char* pConditionName) {for(int id=0; id<GetNbConditions(); id++) { if(!strcmp(pConditionName, GetConditionName(id))) return id; } return -1; };
      //inline const char* GetConditionName(tSMCCondition pConditionId) {if(pConditionId < 0 || pConditionId >= GetNbConditions()) return NULL; else return GetConditionName(pConditionId);} //LOOP
      //inline const char* GetConditionName(int pConditionId) { return GetConditionName(pConditionId); } //LOOP
      inline char GetCondition(tSMCPayload &pSMCPayload, tSMCCondition pCondition) {return GetCondition(mPayload, pCondition);}; 

      int LoadStateTableCSV(const char *pFileName);

      tSMCPayload mPayload;
	  double mPayloadTS;

      int mCurrentStep;
      int mNextStep;
	  const char* GetStepName(const int pStepId) { return (pStepId>0 && pStepId<mStateTableRows ? mStateTable[pStepId][ColStep] : "*NotFound*"); };

      //int   mNbSMCStates;

      enum tSMCColumn {ColStep, ColDesc, ColState, ColDest,  ColNextState, ColSuccess1, ColSuccess2, ColSuccess3, ColFail, ColFailState, ColTimeout, ColAssignations, ColSound, NbStateTableCols};
	  const char* GetTableColumnName(const int pId);
	  const int GetTableColumnId(const char* pName);

	  inline const int GetNbTableRows() { return mStateTableRows;};
	  inline const int GetNbTableColumns() { return mStateTableColumns;};
      inline const char * GetTableElement(const int pRow, const int pCol) { return (pRow<mStateTableRows && pCol<mStateTableColumns && pRow>=0 && pCol>=0 && mStateTable[pRow][pCol] ? mStateTable[pRow][pCol] : "");}

      int PlaySMCSound(const char* pSoundFile);

   protected:

      tSMCModule ParseModuleName(const char * pStrMessage, unsigned int &pPos); //extract module id, good for Src and Dst
      char ParseCode(const char * pStrMessage, unsigned int &pPos);       //extract code (1 char= S R or F)  
      bool ParseNextCondition(const char* pStrMessage, unsigned int &pPos);   //extract 1 condition from string
      tSMCState  ParseStateName(const char* pStrMessage, unsigned int &pPos); //extract state code
      char ParseValue(const char *pStrMessage, unsigned int &pPos);

      int EvaluateConditions(const char* pInputString); //Evaluate multiple conditions, return Nb conditions solved

      bool mOpen;
      char *mStateTableFilename;
      char* mStateTableData;
      int mStateTableDataSize;

      char*** mStateTable;
      int mStateTableRows;
      int mStateTableColumns;

      int InitStateTable();
      void InitConditions();
      void InitModules();

      bool CheckStateTable(); //validate state table - detect whatever is not normal

      bool CheckLists();

      int FindStep(const int pCurrentStep,  const char* pStepName); //solve next step from given name, good for fail state and success state

      static const int NextState          = -1;                   // Default value 
      int mVerboseLevel;
   }; //class CProtocol

} //namespace SMC

#endif // _SMC_PROTOCOL_SERVER_H_



