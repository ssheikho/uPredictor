#include "smcstarthandoverevent.h"
#include "smcconnection.h"
#include "paramlist.h"
#include "pfperson.h"
#include "worldmodel.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

SMCStartHandoverEvent::SMCStartHandoverEvent(
	ParamList *pl, WorldModel *wm, SMCConnection &smcc, PFPerson &person,
	bool liveFire) :
	SMCEventModel(pl, wm, smcc, liveFire), _person(person),
	_state(STATE_NULL) {
	ObjectTable &ot = _pl->getObjectTable();
	int paramObj = _pl->getParamObj(1);
	string obj = ot.getObjectName(paramObj);
	string objNo = "";
	objNo += obj[1];
	_partNo = atoi(objNo.c_str());
}

SMCStartHandoverEvent::~SMCStartHandoverEvent() {}

string SMCStartHandoverEvent::getRobotControlMessage() {
	return "Planner SMC R StartHandover";
}

void SMCStartHandoverEvent::process(const CProtocol::tSMCPayload *payload) {
	if((_state == STATE_START) && (payload->State == CProtocol::HandoverOkay) ){
		_smcc.sendMessage(&_ackMess);
		_state = STATE_INTERMEDIATE;
		_person.setPartNo(_partNo);
		_person.transitionState(PFPerson::TRANS_HANDOVER_COMPLETE);
		_pl->addTime(_sw.lap());
		_wm->apply(*_pl);
	} else if (payload->State == CProtocol::HandoverOkay) {
		_smcc.sendMessage(&_ackMess);
	} else if
		((_state == STATE_START) && 		
		(payload->State == CProtocol::WantStartHandover)
		) {
		_smcc.sendMessage(&_startMess);
	} else if
		((_state == STATE_INTERMEDIATE) &&
		(payload->State != CProtocol::HandoverOkay)&&
		(payload->State != CProtocol::WantStartHandover))
		{
		_state = STATE_END;
	}
}

bool SMCStartHandoverEvent::isDone() {
	//cout<<"SMCStartHandoverEcent::process STATE_END" << endl;
	return _state == STATE_END;
}

void SMCStartHandoverEvent::start() {
	_state = STATE_START;
	cout<<"SMCStartHandoverEcent::process STATE_START" << endl;
	//_smcc.sendMessage(&_startMess);
	_sw.resetAndStart();
}
