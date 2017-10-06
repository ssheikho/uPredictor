#include "smcmovetopersonevent.h"
#include "smcconnection.h"
#include "paramlist.h"
#include "worldmodel.h"

#include <cstring>
#include <iostream>
#include <string>

SMCMoveToPersonEvent::SMCMoveToPersonEvent(
	ParamList *pl, WorldModel *wm, SMCConnection &smcc, bool liveFire) :
	SMCEventModel(pl, wm, smcc, liveFire), _state(STATE_NULL) {}
SMCMoveToPersonEvent::~SMCMoveToPersonEvent() {}

string SMCMoveToPersonEvent::getRobotControlMessage() {
	return "Planner SMC R MoveToPerson";
}

void SMCMoveToPersonEvent::process(const CProtocol::tSMCPayload *payload) {
	if(	(_state == STATE_START) &&
		(payload->State == CProtocol::PartPresentationDone)) {
		//cout << "payload->State == CProtocol::MoveComplete" << endl;
		_state = STATE_END;
		_smcc.sendMessage(&_ackMess);
		_pl->addTime(_sw.lap());
		_wm->apply(*_pl);
	} else if (payload->State == CProtocol::WantMoveToPerson) {
		_smcc.sendMessage(&_startMess);
	} else {
		if(payload->State == CProtocol::PartPresentationDone) {
			//resend ackMess
			_smcc.sendMessage(&_ackMess);
		}
	}
}

bool SMCMoveToPersonEvent::isDone() {
	//cout << "SMCMoveToPersonEvent::process:	STATE_END" <<endl;
	return _state == STATE_END;
}

void SMCMoveToPersonEvent::start() {
	_state = STATE_START;
	cout << "SMCMoveToPersonEvent::process:	STATE_START" <<endl;
	_sw.resetAndStart();
}
