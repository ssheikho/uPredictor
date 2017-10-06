#include "smcmovebackevent.h"
#include "smcconnection.h"
#include "paramlist.h"
#include "worldmodel.h"

#include <cstring>
#include <iostream>
#include <string>

SMCMoveBackEvent::SMCMoveBackEvent(
	ParamList *pl, WorldModel *wm, SMCConnection &smcc, bool liveFire) :
	SMCEventModel(pl, wm, smcc, liveFire), _state(STATE_NULL) {}
SMCMoveBackEvent::~SMCMoveBackEvent() {}

string SMCMoveBackEvent::getRobotControlMessage() {
	return "Planner SMC R StartMoveBack";
}

void SMCMoveBackEvent::process(const CProtocol::tSMCPayload *payload) {
	if(_state == STATE_START) {
		//cout << "SMCMoveBackEvent::process:	STATE_START" <<endl;
		if(payload->State == CProtocol::BackToReadyDone) {
		_state = STATE_END;
		_smcc.sendMessage(&_ackMess);
		_pl->addTime(_sw.lap());
		_wm->apply(*_pl);
		} else if(payload->State == CProtocol::WantMoveBack) {
			//cout << "SMCMoveBackEvent::process:	StartMoveBack" <<endl;
			_smcc.sendMessage(&_startMess);
		}
	}else {
		if(payload->State == CProtocol::BackToReadyDone) {
			//resend ackMess
			_smcc.sendMessage(&_ackMess);
		} else if(payload->State == CProtocol::WantMoveBack) {
			_smcc.sendMessage(&_startMess);
			//cout<<"StartMoveBack sent\n";
		}
	}
}

bool SMCMoveBackEvent::isDone() {
	//cout << "SMCMoveBackEvent::process:	STATE_END" <<endl;
	return _state == STATE_END;
}

void SMCMoveBackEvent::start() {
	cout << "SMCMoveBackEvent::process:	STATE_START" <<endl;
	_state = STATE_START;
	_sw.resetAndStart();
}
