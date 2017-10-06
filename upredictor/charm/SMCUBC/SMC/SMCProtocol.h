//SMCProtocol.h

#ifndef _SMC_PROTOCOL_H_
#define _SMC_PROTOCOL_H_ 

#include <iostream>
#include <string.h>


//#include "SADB.h"

namespace SMC {

   class CProtocol {

   public:
      static const int MaxMessageLen      = 128;   //in bytes

      CProtocol() {   

         // InitConditions(); 

         // InitModules();

         // InitStates();
      };

      ~CProtocol() {
         //if(mSMCStateNames)
         //	  delete mSMCStateNames;
         //mNbSMCStates = 0;

         //SADB based
         //if(mStateTable)
         //	  delete mStateTable;
         //mStateTable = NULL;
      };

      //enum for boolean type
      //we need TRUE, FALSE and NA
      //some function will be needed to check if TRUE (can't use the bool directly in if)
      enum tSMCBool : char {eFALSE=0, eTRUE=1, eNA=2};

      //Entity enum and Entity names
      //NOTE: we can match these with 4 bytes = int time in a switch/case

      enum SMCModule : char {
         NONE=0,
         SMC,
         SADB,
         T1,
         T2,
         T3,
         T3P,
         T3W,
         T3O,
         T3K,
         IAD,
         KUKA,
         GRIP,
         Planner,
         ALL,
         NbSMCModules,
         UNKNOWN
      };

      typedef SMCModule tSMCModule;

      //static const char* mSMCModuleNames[NbSMCModules];

      //each state correspond to an enum with the same name
      enum tSMCState : char {
         STATE_UNKNOWN,

         //Global (For SMC)
         Begin,
         End,
         Wait, 
         Initialization,
         InitTaskInfo,
         LoadScript,
         Iterate,
         Finish,

         //For T1
         //         InitT1,
         //         T1DeliverPart,
         //	     T1RetractTray,
         //         FinishT1,

         //For T2
         //         InitT2,
         //         T2GotoSupply,
         //         T2GotoDelivery,
         //         T2Finish,

         //IAD
         InitIAD,
         //		 MoveIADToReadyPosition,
         //		 MoveIADToHandoverPosition,
         //		 MoveIADToRestPosition,
         IADFinish,

         //Kuka
         InitKUKA,
         PathPlanning,
         Inspection1,
         Inspection2,
         PointToFaultyPart1,
         AcknowledgeRequest,
         MoveToReadyPosition,
         MoveToHandoverPosition,
         MoveToRestPosition,
         FetchApproach1,
         FetchApproach2,
         FetchApproach3,
         Fetch1,
         Fetch2,
         Fetch3,
         Retract1,
         Retract2,
         Retract3,
         //		 RetractArm,
         FinishKUKA,

         //Gripper
         InitGRIP,
         CloseGRIP,
         //		 CloseNormalGRIP,
         OpenGRIP,
         //		 OpenNormalGRIP,
         OneFingerGRIP,
         CloseTipGRIP,
         BiasGRIP,
         Handover,
         TapDetector,
         FinishGRIP,

         //For T3K
         InitT3K,
         FinishT3K,

         //For T3W
         InitT3W,
         CheckWorker,
         HumanReady,
         HumanReadyToReceive,
         RequestReplacement,
         IndicateDone,
         //		 IndicateDoneWithCorrection,
         //		 IndicateDoneWithAssembly,
         FinishT3W,

         //For T3P
         InitT3P,
         CheckParts,
         FinishT3P,

         //For T3O
         InitT3O,
         StartCollisionCheck,
         CollisionAvoidance,
         CheckFreeSpace,
         //         CheckFreeSpaceS,
         //         CheckFreeSpaceD,
         FinishT3O,

         //Planner stuff
         StartPlanner,

         DoWhatNext,
         DoWhatNext1,
         DoWhatNext2,
         DoWhatNext3,

         WantStartMove,
         WantStartMove1,
         WantStartMove2,
         WantStartMove3,
         WantStartMove4,
         WantStartMove5,

         MoveComplete,
         MoveComplete1,
         MoveComplete2,
         MoveComplete3,
         MoveComplete4,
         MoveComplete5,
         MoveComplete6,

         WantStartPartPresentation,
         WantStartPartPresentation1,
         WantStartPartPresentation2,
         WantStartPartPresentation3,

         PartPresentationDone,
         PartPresentationDone1,
         PartPresentationDone2,
         PartPresentationDone3,

         WantStartHandover,
         WantStartHandover1,
         WantStartHandover2,
         WantStartHandover3,

         //Handover
         Handover1,
         Handover2,
         Handover3,
         HandoverOkay,

         BackToReadyDone,
         BackToReadyDone1,
         BackToReadyDone2,
         BackToReadyDone3,

         WantMoveToPerson,
         WantMoveBack,

         NbSMCStates //compute Nb
      };


      //char* mSMCStateNames;
      //int mNbSMCStates;
      //int* mSMSStateID; //implicit

      // condition enum and names

      enum tSMCCondition {
         //General system
         AllOk,
         PartCount,
         NextPart,
         CurrentPart,
         FetchPart,
         FaultyPart,
         //		 PositionKUKA,
         //		 PositionIAD,
         Position,
         GRIPPosition,

         //SMC
         SMCReady,
         SMCFailed,

         //SADB
         SADBReady,
         //		 SADBInProgress,
         SADBFailed,

         //From T1
         T1Ready,
         WaitingForWorker,
         PresentingPart,
         WaitingForPickup,
         PartPickedUp,
         RetractingTray,
         TrayRetracted,
         T1Done,
         T1Failed,

         //From T2-T2
         T2Ready,
         T2Moving,
         T2MoveComplete,
         T2Done,
         T2Failed,

         //From T2-IAD
         IADReady,
         IADMoving,
         IADMoveComplete,
         IADDone,
         IADFailed,
         PathOK,

         //From T2-KUKA
         KUKAReady,
         KUKAMoving,
         KUKAMoveComplete,
         KUKADone,
         KUKAFailed,

         //From T2-GRIP
         GRIPReady,
         GRIPMoving,
         GRIPClose,
         //		 GRIPCloseNormal,
         GRIPOpen,
         //		 GRIPOpenNormal,
         GRIPOneFinger,
         GRIPDone,
         GRIPFailed,
         TapDetected,
         GRIPMode,
         HandoverComplete,
         HandoverFailed,

         //From T3W
         T3WInProgress,
         T3WReady,
         WorkerPresent,
         T3WFailed,
         WorkerReadyForPart,
         WorkerAssemblyDone,
         WorkerHandUp,
         WorkerInMainWorkspace,
         WorkerInSideWorkspace,
         //T3W since PF3
         WorkerFacingDoor,
         WorkerBothHandsOnDoor,
         WorkerWorkingOnDoor,
         WorkerDisposedBadPart, 
         WorkerInstalledPart,    
         WorkerRemovedPart,

         //From T3P
         T3PInProgress,
         T3PReady,
         PartOnTray,
         PartInPlace,
         PartTaken,
         T3PFailed,
         Part1Installed,
         Part1Checked,
         Part1OK,
         Part1Failed,
         Part2Installed,
         Part2Checked,
         Part2OK,
         Part2Failed,
         AssemblyComplete,
         AssembledPartId,
         TestedPartId,

         //From T3O
         T3OInProgress,
         T3OReady,
         FreeSpace,
         NoSpace,
         //       FreeSpaceToSupply,
         //       FreeSpaceToDeliver,
         //		 NoSpaceToSupply,
         //		 NoSpaceToDeliver,
         T3OFailed,

         //From T3K
         T3KReady,
         T3KInProgress,
         T3KFailed,

         //From Planner

         PlannerReady,
         PlannerFailed, 
         PlannerFinish, 
         PlannerACK, 
         PlannerNACK,
         StartMove1,
         StartMove2,
         StartMove3, 
         PlannerDontGo, 
         StartHandover1, 
         StartHandover2,
         PresentPart1, 
         PresentPart2,
         PresentPart3, 
         BadPart1,
         BadPart2,
         BadPart3,

		GetPart,
		MoveToPerson,
		StartMoveBack,
		
		

         //reserved
         //UNKNOWN_CONDITION,
         NbSMCConditions //auto compute Nb in list +1
      };

      //TODO DO: must add support here for variable number of conditions... 

      typedef struct 
      {
         tSMCModule Src;                                    //enum : char
         tSMCModule Dst;                                    //enum : char
         char       Code;                                   //char (R S or F)
         tSMCState  State;                                  //enum : char
         int        Step;                                   //enum : char
         char		Conditions[(const int)NbSMCConditions]; //array of conditions, use TSMCBool OR char to read
         char       Padding[(NbSMCConditions%8)?NbSMCConditions%8:8]; //Padding for alignment on 64bit/8bytes an avoid sizeof problems between different compiler
         char Message[MaxMessageLen];                       //actually MaxMessageLen bytes max, including \n and \0 (Pos 0)
      } tSMCPayload;

      //support for variable length text strings (may help for multiple conditions)
      inline int GetActualPayloadSize(tSMCPayload* pMessage) {return sizeof(tSMCPayload) - (MaxMessageLen - strlen(pMessage->Message));};

      //Get/Set Conditions in payload structure
      static char GetCondition(tSMCPayload &pSMCPayload, tSMCCondition pCondition) {return pSMCPayload.Conditions[pCondition];};

      /*
      //void SADBAddInteger(const char* pName, const int pValue, const char* pDescription = NULL);
      //int  SADBGetInteger(const char* pName);

      //int SADBAddString(const char* pName, const char* pString, const char* pDescription = NULL);
      //int SADBGetString(const char* pName, char* &pString);

      //int SADBAddByteArray(const char* pName, const char* pBytes, int pLen, const char* pDescription = NULL);
      //int SADBGetByteArray(const char* pName, char* &pBytes, int &pLen);

      //int SADBAddStringArray(const char* pName, const char* pStrings[], int pNbStrings, const char* pDescription = NULL);
      //int SADBGetStringArray(const char* pName, char** &pStrings, int &pNbStrings, int &pLen);

      //int SMCServer::SADBAddStringArray2D(const char* pName, const char*** pStrings, int pNbRows, int pNbColumns, const char* pDescription = NULL);
      */

      /*
      int InitStateTable(const char* pName = "SMC.StateTable");
      int InitShadowTable(const char* pName = "SMC.ShadowTable");


      static const int ColumnNames = 0;
      static const int RowHeaders = 0;
      */

      //int InitConditions();
      static int GetNbConditions()  { return NbSMCConditions; }; 

      static tSMCCondition GetConditionId(const char* pName);
      static const char* GetConditionName(const int pId);

      //int InitModules();
      static int GetNbModules() { return NbSMCModules; };

      static tSMCModule GetModuleId(const char * pName);
      static const char* GetModuleName(const int pId);
      static bool IsMandatoryModule(const char * pName);
      static bool IsMandatoryModule(const int pId);

      //int InitStates();
      static const char* GetStateName(int pIdState);
      static tSMCState GetStateId(const char* pName);
      //static int GetNbStates();

      inline int GetNbStates() { return NbSMCStates;}

   }; //class CProtocol


} //namespace SMC

#endif // _SMC_PROTOCOL_H_



