#include "smcgetpartevent.h"
#include "smcconnection.h"
#include "paramlist.h"
#include "worldmodel.h"

#include <cstring>
#include <string>

SMCGetPartEvent::SMCGetPartEvent(ParamList *pl, WorldModel *wm,
	SMCConnection &smcc, bool liveFire) :
	SMCEventModel(pl, wm, smcc, liveFire), _state(STATE_NULL) {}
SMCGetPartEvent::~SMCGetPartEvent() {}

string SMCGetPartEvent::getRobotControlMessage() {
	string retVal = "";	
	int ParamObject = 0;	
	string ParamObjectName = "";
	ParamObject = _pl->getParamObj(1);
	ParamObjectName = _pl->getObjectTable().getObjectName(ParamObject);

	if(strcmp(ParamObjectName.c_str(), "p1") == 0) {
		retVal = "Planner SMC R GetPart FetchPart=1";
	} else if(strcmp(ParamObjectName.c_str(), "p2") == 0) {
		retVal = "Planner SMC R GetPart FetchPart=2";
	} else if(strcmp(ParamObjectName.c_str(), "p3") == 0) {
		retVal = "Planner SMC R GetPart FetchPart=3";
	} else if(strcmp(ParamObjectName.c_str(), "p4") == 0) {
		retVal = "Planner SMC R GetPart FetchPart=4";
	}

	return retVal;
}

void SMCGetPartEvent::process(const CProtocol::tSMCPayload *payload) {
	//cout << "SMCGetPartEvent::process" << endl;
	if(_state == STATE_START){
		//cout << "SMCGetPartEvent::process:	STATE_START" << endl;
		if(payload->State == CProtocol::MoveComplete) {
			//cout << "SMCGetPartEvent::process:	STATE_START	MoveComplete" <<
			//	endl;
			//Send ACK
			_smcc.sendMessage(&_ackMess);
			
			//Affects planner
			_state = STATE_END;
			_pl->addTime(_sw.lap());
			_wm->apply(*_pl);
			//cout << "/SMCGetPartEvent::process:	STATE_START	MoveComplete" <<
			//	endl;
		} else if(payload->State == CProtocol::WantStartMove) {
			_smcc.sendMessage(&_startMess);
			//_sw.resetAndStart();
		} 
	} else {
		if(payload->State == CProtocol::MoveComplete) {
			//resend ackMess
			_smcc.sendMessage(&_ackMess);
		} else if(payload->State == CProtocol::WantStartMove) {
			_smcc.sendMessage(&_startMess);
			//_sw.resetAndStart();
		} 
	}
}

bool SMCGetPartEvent::isDone() {
	//cout<<"SMCGetPartEvent::process STATE_END" << endl;
	return _state == STATE_END;
}

void SMCGetPartEvent::start() {
	_state = STATE_START;
	cout<<"SMCGetPartEvent::process STATE_START" << endl;
	//_smcc.sendMessage(&_startMess);
	_sw.resetAndStart();
}
