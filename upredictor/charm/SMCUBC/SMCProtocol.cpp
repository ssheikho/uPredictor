// SMCProtocol.cpp
//

//#include <iostream>
#include "SMC/SMCProtocol.h"
#include <string.h>
#include <stdio.h>

using namespace SMC;
using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//CONDITIONS


//const char* SMC::CProtocol::mSMCConditionNames[SMC::CProtocol::NbSMCConditions];

SMC::CProtocol::tSMCCondition SMC::CProtocol::GetConditionId(const char* pName)
{
	int lId=0;

	//support empty strings
	if(pName==NULL)
		return (tSMCCondition)lId;

	for(int lCondId=0; lCondId<NbSMCConditions; lCondId++)
	{
		if(!strcmp(pName, GetConditionName(lCondId)))
		{
			lId = (tSMCCondition)lCondId;
			return (tSMCCondition)lId;
		}
	}

	cout << "Condition " << pName << " not found!!!!!!" << endl;

	return (tSMCCondition)lId;
}

const char* SMC::CProtocol::GetConditionName(const int pId)
{
	//out of bounds
	if(pId < 0 || pId >= GetNbConditions()) 
		return "UNKNOWN_CONDITION"; //return "";   //NOTE: on pourrait retourner NULL
	
	//string available in cache
	//if(mSMCConditionNames[pId])
	//	return mSMCConditionNames[pId];

	//string not define yet (default)
	
	switch(pId)
	{
		//General system - Counters
		case AllOk: return "AllOk"; break;
		case NextPart: return "NextPart"; break;
		case PartCount: return "PartCount"; break;
		case Position: return "Position"; break;
		case GRIPPosition: return "GRIPPosition"; break;
//		case PositionIAD: return "PositionIAD"; break;
//		case PositionKUKA: return "PositionKUKA"; break;
		case CurrentPart: return "CurrentPart"; break;
		case FetchPart: return "FetchPart"; break;
		case FaultyPart: return "FaultyPart"; break;
			
		//SMC
		case SMCReady: return "SMCReady"; break;
		case SMCFailed: return "SMCFailed"; break;
		
		//SADB
		case SADBReady: return "SADBReady"; break;
		case SADBFailed: return "SADBFailed"; break;

		//From T1
		case T1Ready: return "T1Ready"; break;
		case WaitingForWorker: return "WaitingForWorker"; break;
		case PresentingPart: return "PresentingPart"; break;
		case WaitingForPickup: return "WaitingForPickup"; break;
		case PartPickedUp: return "PartPickedUp"; break;
		case RetractingTray: return "RetractingTray"; break;
		case TrayRetracted: return "TrayRetracted"; break;
		case T1Done: return "T1Done"; break;
		case T1Failed: return "T1Failed"; break;

		//From T2
		case T2Ready: return "T2Ready"; break;
		case T2Moving: return "T2Moving"; break;
		case T2MoveComplete: return "T2MoveComplete"; break;
		case T2Done: return "T2Done"; break;
		case T2Failed: return "T2Failed"; break;

		//From IAD
		case IADReady: return "IADReady"; break;
		case IADMoving: return "IADMoving"; break;
		case IADMoveComplete: return "IADMoveComplete"; break;
		case IADDone: return "IADDone"; break;
		case IADFailed: return "IADFailed"; break;
		case PathOK: return "PathOK"; break;
			
		//From Kuka
		case KUKAReady: return "KUKAReady"; break;
		case KUKAMoving: return "KUKAMoving"; break;
		case KUKAMoveComplete: return "KUKAMoveComplete"; break;
		case KUKADone: return "KUKADone"; break;
		case KUKAFailed: return "KUKAFailed"; break;

		//From Gripper
		case GRIPReady: return "GRIPReady"; break;
		case GRIPMoving: return "GRIPMoving"; break;
		case GRIPClose: return "GRIPClose"; break;
		case GRIPOpen: return "GRIPOpen"; break;
//		case GRIPCloseNormal: return "GRIPCloseNormal"; break;
//		case GRIPOpenNormal: return "GRIPOpenNormal"; break;
		case GRIPOneFinger: return "GRIPOneFinger"; break;
		case GRIPDone: return "GRIPDone"; break;
		case GRIPFailed: return "GRIPFailed"; break;
		case TapDetected: return "TapDetected"; break;
//		case TapNotDetected: return "TapNotDetected"; break;
		case GRIPMode: return "GRIPMode"; break;
		case HandoverComplete: return "HandoverComplete"; break;
		case HandoverFailed: return "HandoverFailed"; break;

		//From T3W
		case T3WInProgress: return "T3WInProgress"; break;
		case T3WReady: return "T3WReady"; break;
		case WorkerPresent: return "WorkerPresent"; break;
		case T3WFailed: return "T3WFailed"; break;
		case WorkerReadyForPart: return "WorkerReadyForPart"; break;
		case WorkerAssemblyDone: return "WorkerAssemblyDone"; break;
		case WorkerHandUp: return "WorkerHandUp"; break;
		case WorkerInMainWorkspace: return "WorkerInMainWorkspace"; break;
		case WorkerInSideWorkspace: return "WorkerInSideWorkspace"; break;

		//T3W since PF3
		case WorkerFacingDoor: return "WorkerFacingDoor"; break;
		case WorkerBothHandsOnDoor: return "WorkerBothHandsOnDoor"; break;
		case WorkerWorkingOnDoor: return "WorkerWorkingOnDoor"; break;
		case WorkerDisposedBadPart: return "WorkerDisposedBadPart"; break;
		case WorkerInstalledPart: return "WorkerInstalledPart"; break;
		case WorkerRemovedPart: return "WorkerRemovedPart"; break;
			
		//From T3P
		case T3PInProgress: return "T3PInProgress"; break;
		case T3PReady: return "T3PReady"; break;
		case PartOnTray: return "PartOnTray"; break;
		case PartInPlace: return "PartInPlace"; break;
		case PartTaken: return "PartTaken"; break;
		case AssemblyComplete: return "AssemblyComplete"; break;
		case T3PFailed: return "T3PFailed"; break;
		case Part1Installed: return "Part1Installed"; break;
		case Part1Checked: return "Part1Checked"; break;
		case Part1OK: return "Part1OK"; break;
		case Part1Failed: return "Part1Failed"; break;
		case Part2Installed: return "Part2Installed"; break;
		case Part2Checked: return "Part2Checked"; break;
		case Part2OK: return "Part2OK"; break;
		case Part2Failed: return "Part2Failed"; break;
		case AssembledPartId: return "AssembledPartId"; break; //counters
		case TestedPartId: return "TestedPartId"; break; //counters

		//From T3O
		case T3OInProgress: return "T3OInProgress"; break;
		case T3OReady: return "T3OReady"; break;
		case FreeSpace: return "FreeSpace"; break;
		case NoSpace: return "NoSpace"; break;
//		case NoSpaceToSupply: return "NoSpaceToSupply"; break;
//		case NoSpaceToDeliver: return "NoSpaceToDeliver"; break;
//		case FreeSpaceToSupply: return "FreeSpaceToSupply"; break;
//		case FreeSpaceToDeliver: return "FreeSpaceToDeliver"; break;
		case T3OFailed: return "T3OFailed"; break;

			//From T3K
		case T3KReady: return "T3KReady"; break;
		case T3KInProgress: return "T3KInProgress"; break;
		case T3KFailed: return "T3KFailed"; break;

			//From Planner
		case PlannerReady: return "PlannerReady"; break;
		case PlannerFailed: return "PlannerFailed"; break;
		case PlannerFinish: return "PlannerFinish"; break;
		case PlannerACK: return "PlannerACK"; break;
		case PlannerNACK: return "PlannerNACK"; break;
		case StartMove1: return "StartMove1"; break;
		case StartMove2: return "StartMove2"; break;
		case StartMove3: return "StartMove3"; break;
		case PlannerDontGo: return "PlannerDontGo"; break;
		case StartHandover1: return "StartHandover1"; break;
		case StartHandover2: return "StartHandover2"; break;
		case PresentPart1: return "PresentPart1"; break;
		case PresentPart2: return "PresentPart2"; break;
		case PresentPart3: return "PresentPart3"; break;
		case BadPart1: return "BadPart1"; break;
		case BadPart2: return "BadPart2"; break;
		case BadPart3: return "BadPart3"; break;

		case GetPart: return "GetPart"; break;
		case MoveToPerson: return "MoveToPerson"; break;
		case StartMoveBack: return "StartMoveBack"; break;

	//case UNKNOWN_CONDITION:
	default:
		cout << "Condition " << pId << "UNKNOWN_CONDITION!" << endl;
		return "UNKNOWN_CONDITION";
		break;
	}

	return NULL;
}

/*
int SMC::CProtocol::InitConditions()
{
	int lCondId=0;

	cout << "InitConditions..." << endl;

	//for(;lCondId<NbSMCConditions; lCondId++)
	//	mSMCConditionNames[lCondId] = GetConditionName(lCondId);

	cout << "InitConditions OK" << endl;

	return lCondId; //NbSMCConditions
}
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//MODULES

//const char* SMC::CProtocol::mSMCModuleNames[SMC::CProtocol::NbSMCModules];

/*
int SMC::CProtocol::InitModules()
{
	int lModId = 0;
	//for(;lModId< GetNbModules(); lModId++)
	//	mSMCModuleNames[lModId] = GetModuleName(lModId);

	return lModId;
}
*/





SMC::CProtocol::tSMCModule SMC::CProtocol::GetModuleId(const char * pName)
{
	tSMCModule lId = CProtocol::NONE;
	for(int lModuleId=0; lModuleId<GetNbModules(); lModuleId++)
	{
		if(!strcmp(pName, GetModuleName(lModuleId)))
		{
			lId = (tSMCModule)lModuleId;
			break;
		}
	}

	return lId;
}


const char* SMC::CProtocol::GetModuleName(const int pId)
{
	if(pId < 0 || pId >= GetNbModules())
		return NULL;

	//if(mSMCModuleNames[pId] != NULL)
	//	return mSMCModuleNames[pId];

	switch(pId)
	{
		case NONE: return "NONE"; break;
		case SMC: return "SMC"; break;
		case SADB: return "SADB"; break;
		case T1: return "T1"; break;
		case T2: return "T2"; break;
		case T3: return "T3"; break;
		case T3P: return "T3P"; break;
		case T3W: return "T3W"; break;
		case T3O: return "T3O"; break;
		case T3K: return "T3K"; break;
		case IAD: return "IAD"; break;
		case KUKA: return "KUKA"; break;
		case GRIP: return "GRIP"; break;
		case Planner: return "Planner"; break;
		case ALL: return "ALL"; break;
		case UNKNOWN: return "UNK"; break;

		default:
			cout << "getModuleName() pId=" << pId << " is unknown!" << endl;
			break;
	}

	return NULL;
}

bool SMC::CProtocol::IsMandatoryModule(const int pId)
{
	switch(pId)
	{

		case T3W:
		case T3O:
		case T3K:
		case IAD:
		case KUKA:
		case GRIP:
			return true;
			break;

		case SMC: //temp -> is true at SMC
		case SADB: //temp -> must be true
		case Planner: //temp -> will become true
		case T1:
		case T2:
		case T3:
		case T3P:
		case ALL:
		case NONE:
			return false;
			break;

		default:
			cout << "Warning: isMandatoryModule() pId=" << pId << " not recognized!" << endl;
			return false;
			break;
	}

	return false;
}


bool SMC::CProtocol::IsMandatoryModule(const char * pName)
{
	if(pName==NULL)
		return false;

	return IsMandatoryModule(GetModuleId(pName));
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//STATES


//const char* SMC::CProtocol::mSMCStateNames[SMC::CProtocol::NbSMCStates];

const char* SMC::CProtocol::GetStateName(int pIdState)
{

	//init strings

	if(pIdState < 0 || pIdState > NbSMCStates)
	{
		cout << "GetStateName("<< pIdState <<") Unknown State!" << endl;
		//return "UNKNOWN";
		return NULL;
	}

	//cached?
	//if(mSMCStateNames[pIdState] != NULL)
	//	return mSMCStateNames[pIdState];

	switch((tSMCState)pIdState)
	{
			//Global
		case Begin:			   	return "Begin"; break;
		case End:			   	return "End"; break;
		case Wait:			   	return "Wait"; break;
		case Initialization:	return "Initialization"; break;
		case InitTaskInfo:		return "InitTaskInfo"; break;
		case LoadScript:		return "LoadScript"; break;
		case Finish:			return "Finish"; break;
		case Iterate:			return "Iterate"; break;

			//For T1
//		case InitT1:			return "InitT1"; break;
//		case T1DeliverPart:		return "T1DeliverPart"; break;
//		case T1RetractTray:		return "T1RetractTray"; break;
//		case FinishT1:		   	return "FinishT1"; break;

			//For T2
//		case InitT2:			return "InitT2"; break;
//		case T2GotoSupply:      return "T2GotoSupply"; break;
//		case T2GotoDelivery:    return "T2GotoDelivery"; break;
//		case T2Finish:			return "T2Finish"; break;

			//For T3W
		case InitT3W:			return "InitT3W"; break;
		case CheckWorker:       return "CheckWorker"; break;
		case HumanReady:		return "HumanReady"; break;
		case HumanReadyToReceive: return "HumanReadyToReceive"; break;
		case RequestReplacement: return "RequestReplacement"; break;
		case IndicateDone:		return "IndicateDone"; break;
//		case IndicateDoneWithAssembly: return "IndicateDoneWithAssembly"; break;
//		case IndicateDoneWithCorrection: return "IndicateDoneWithCorrection"; break;
		case FinishT3W:			return "FinishT3W"; break;

			//For T3K
		case InitT3K:			return "InitT3K"; break;
		case FinishT3K:			return "FinishT3K"; break;

			//For T3P
		case InitT3P:			return "InitT3P"; break;
		case CheckParts:        return "CheckParts"; break;
		case FinishT3P:			return "FinishT3P"; break;

			//For T3O
		case InitT3O:		   	return "InitT3O"; break;
		case StartCollisionCheck: 	return "StartCollisionCheck"; break;
		case CollisionAvoidance: return "CollisionAvoidance"; break;
		case CheckFreeSpace:    return "CheckFreeSpace"; break;
//		case CheckFreeSpaceS:   return "CheckFreeSpaceS"; break;
//		case CheckFreeSpaceD:   return "CheckFreeSpaceD"; break;
		case FinishT3O:	   		return "FinishT3O"; break;

			//IAD
		case InitIAD:	   		return "InitIAD"; break;
//		case MoveIADToReadyPosition: return "MoveIADToReadyPosition"; break;
//		case MoveIADToHandoverPosition: return "MoveIADToHandoverPosition"; break;
//		case MoveIADToRestPosition:		return "MoveIADToRestPosition"; break;
		case IADFinish:	   		return "IADFinish"; break;

			//KUKA
		case InitKUKA:		   	return "InitKUKA"; break;
		case PathPlanning:		return "PathPlanning"; break;
		case Inspection1:		return "Inspection1"; break;
		case Inspection2:		return "Inspection2"; break;
		case PointToFaultyPart1: return "PointToFaultyPart1"; break;
		case AcknowledgeRequest: return "AcknowledgeRequest"; break;
		case MoveToReadyPosition:	return "MoveToReadyPosition"; break;
		case MoveToHandoverPosition: return "MoveToHandoverPosition"; break;
		case MoveToRestPosition: return "MoveToRestPosition"; break;
		case FetchApproach1:  	return "FetchApproach1"; break;
		case FetchApproach2:  	return "FetchApproach2"; break;
		case FetchApproach3:  	return "FetchApproach3"; break;
		case Fetch1:			return "Fetch1"; break;
		case Fetch2:  			return "Fetch2"; break;
		case Fetch3:		 	return "Fetch3"; break;
		case Retract1:	  		return "Retract1"; break;
		case Retract2:	  		return "Retract2"; break;
		case Retract3:	   		return "Retract3"; break;
//		case RetractArm:	   	return "RetractArm"; break;
		case FinishKUKA:	   	return "FinishKUKA"; break;

			//GRIPPER
		case InitGRIP:	   		return "InitGRIP"; break;
		case CloseGRIP:	   		return "CloseGRIP"; break;
		case CloseTipGRIP:	   	return "CloseTipGRIP"; break;
//		case CloseNormalGRIP:	return "CloseNormalGRIP"; break;
		case OpenGRIP:	   		return "OpenGRIP"; break;
//		case OpenNormalGRIP:	return "OpenNormalGRIP"; break;
		case OneFingerGRIP:		return "OneFingerGRIP"; break;
		case Handover:	   		return "Handover"; break;
		case TapDetector:	   	return "TapDetector"; break;
		case FinishGRIP:	   	return "FinishGRIP"; break;
	    case BiasGRIP:	   		return "BiasGRIP"; break;


			//For Planner

		case StartPlanner:	  	return "StartPlanner"; break;

		case DoWhatNext:	  	return "DoWhatNext"; break;
		case DoWhatNext1:	   	return "DoWhatNext1"; break;
		case DoWhatNext2:	   	return "DoWhatNext2"; break;
		case DoWhatNext3:	   	return "DoWhatNext3"; break;

		case WantStartMove:	   	return "WantStartMove"; break;
		case WantStartMove1:	return "WantStartMove1"; break;
		case WantStartMove2:	return "WantStartMove2"; break;
		case WantStartMove3:	return "WantStartMove3"; break;
		case WantStartMove4:	return "WantStartMove4"; break;
		case WantStartMove5:	return "WantStartMove5"; break;

		case MoveComplete:	   	return "MoveComplete"; break;
		case MoveComplete1:	   	return "MoveComplete1"; break;
		case MoveComplete2:	   	return "MoveComplete2"; break;
		case MoveComplete3:	   	return "MoveComplete3"; break;
		case MoveComplete4:	   	return "MoveComplete4"; break;
		case MoveComplete5:	   	return "MoveComplete5"; break;
		case MoveComplete6:	   	return "MoveComplete6"; break;

		case WantStartPartPresentation:	 return "WantStartPartPresentation"; break;
		case WantStartPartPresentation1: return "WantStartPartPresentation1"; break;
		case WantStartPartPresentation2: return "WantStartPartPresentation2"; break;
		case WantStartPartPresentation3: return "WantStartPartPresentation3"; break;

		case PartPresentationDone:	return "PartPresentationDone"; break;
		case PartPresentationDone1:	return "PartPresentationDone1"; break;
		case PartPresentationDone2:	return "PartPresentationDone2"; break;
		case PartPresentationDone3:	return "PartPresentationDone3"; break;

		case WantStartHandover:	   	return "WantStartHandover"; break;
		case WantStartHandover1:	return "WantStartHandover1"; break;
		case WantStartHandover2:	return "WantStartHandover2"; break;
		case WantStartHandover3:	return "WantStartHandover3"; break;

				//Handover
		case Handover1:	   		return "Handover1"; break;
		case Handover2:	   		return "Handover2"; break;
		case Handover3:	   		return "Handover3"; break;
		case HandoverOkay:	   	return "HandoverOkay"; break;

		case BackToReadyDone:	   	return "BackToReadyDone"; break;
		case BackToReadyDone1:	   	return "BackToReadyDone1"; break;
		case BackToReadyDone2:	   	return "BackToReadyDone2"; break;
		case BackToReadyDone3:	   	return "BackToReadyDone3"; break;

		case WantMoveToPerson:	   	return "WantMoveToPerson"; break;
		case WantMoveBack:	   		return "WantMoveBack"; break;

			//default to unknown
		case STATE_UNKNOWN:     return "UNKNOWN_STATE"; break;

		default:
			cout << "GetStateName(" << pIdState << ") Unknown!" << endl;
			return "UNKNOWN";
			break;
	}

	return NULL;
}


SMC::CProtocol::tSMCState SMC::CProtocol::GetStateId(const char* pName)
{
	for(int lIdState=Begin; lIdState<SMC::CProtocol::NbSMCStates; lIdState++)
		if(!strcmp(GetStateName(lIdState), pName))
			return (tSMCState)lIdState;

	cout << "GetIdState() unknown name " << pName << " !" << endl;

	//not found
	return STATE_UNKNOWN;
}

/*
int SMC::CProtocol::InitStates()
{
	int lStateId=0;

	cout << "InitStates..." << endl;

	for(  ; lStateId < GetNbStates(); lStateId++)
	{
	//	mSMCStateNames[lStateId] = GetStateName(lStateId);
	}

	cout << "InitStates OK" << endl;

	return lStateId;
}
*/



//end of file SMCProtocol.cpp
