#include "smceventmodel.h"
#include "smcconnection.h"
#include "worldmodel.h"

#include <cstring>
#include <iostream>

using namespace std;

SMCEventModel::SMCEventModel(ParamList *pl, WorldModel *wm, SMCConnection &smcc,
	 bool liveFire) : _pl(pl), _wm(wm), _smcc(smcc), _liveFire(liveFire),
	_startMess(this) {}
SMCEventModel::~SMCEventModel() {}

void SMCEventModel::sendAck() {
	cout << "ACK" << endl;
}

void SMCEventModel::sendRobotControlMessage() {
	if(_liveFire) {
		//smcc.sendMessage();
	} else {
		cout << getRobotControlMessage() << endl;
		_wm->apply(*_pl);
	}
}

SMCEventModel::StartMessage::StartMessage(SMCEventModel *em) : _em(em) {}
SMCEventModel::StartMessage::~StartMessage() {}

void SMCEventModel::StartMessage::packMessage(char *payload) {
	string mess = _em->getRobotControlMessage();
	strcpy(payload, mess.c_str());
}

SMCEventModel::AckMessage::AckMessage() {}
SMCEventModel::AckMessage::~AckMessage() {}

void SMCEventModel::AckMessage::packMessage(char *payload) {
	string mess = "Planner SMC R PlannerACK";
	strcpy(payload, mess.c_str());
}
