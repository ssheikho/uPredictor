#include "pfperson.h"
#include "paramlist.h"
#include "planninggraph.h"
#include "problem.h"
#include "smcconnection.h"
#include "worldmodel.h"

#include <unistd.h>

#include <cstdlib>

PFPerson::PFPerson(SMCConnection &smc, WorldModel &wm) :
	_state(STATE_HAND_EMPTY_NO_PART), _partNo(0), _wm(wm),
	_plt(_wm.getCurrentState()->getProblem().getPG().getPLT()),
	_thePerson("per1"),
	_lastState(-1) {
	smc.addMessageHandler(this);
	_m[1] = new PartInfo("p1", "d1", "ptype1");
	_m[2] = new PartInfo("p2", "d1", "ptype1");
	_m[3] = new PartInfo("p3", "d2", "ptype2");
	_m[4] = new PartInfo("p4", "d2", "ptype2");
}

PFPerson::~PFPerson() {}

void PFPerson::transitionState(int stateTransition) {
	//cout << "PFPerson::transitionState:	" << _state << "	" <<
	//	stateTransition << endl;
	bool transitionSuccessful = false;

	switch(_state) {
		case STATE_HAND_EMPTY_NO_PART:
			switch(stateTransition) {
				case TRANS_HANDOVER_COMPLETE:
					_state = STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET;
					transitionSuccessful = true;
					_sw.resetAndStart();	//RESET TIMER
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_NO_PART -- TRANS_HANDOVER_COMPLETE -- STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET" << endl;
					break;
				case TRANS_WORKER_WORKING_ON_DOOR:
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_NO_PART -- (TRANS_HANDOVER_COMPLETE) -- STATE_HAND_EMPTY_NO_PART" << endl;
					break;
				case TRANS_WORKER_NOT_WORKING_ON_DOOR:
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_NO_PART -- (TRANS_WORKER_NOT_WORKING_ON_DOOR) -- STATE_HAND_EMPTY_NO_PART" << endl;
					break;
				case TRANS_WORKER_DISPOSED_PART:
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_NO_PART -- (TRANS_WORKER_DISPOSED_PART) -- STATE_HAND_EMPTY_NO_PART" << endl;
					personDiscardsPart(_partNo);	//Records time, resets timer
					break;
			}
			break;

		case STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET:
			switch(stateTransition) {
				case TRANS_HANDOVER_COMPLETE:
					if(_lastState != _state)
						cout << "STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET -- (TRANS_HANDOVER_COMPLETE) -- STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET" << endl;
					break;

				case TRANS_WORKER_WORKING_ON_DOOR:
					_state = STATE_WORKING_ON_DOOR;
					transitionSuccessful = true;
					if(_lastState != _state)
						cout << "STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET -- TRANS_WORKER_WORKING_ON_DOOR -- STATE_WORKING_ON_DOOR" << endl;
					//NO OTHER ACTIONS REQUIRED
					break;

				case TRANS_WORKER_NOT_WORKING_ON_DOOR:
					if(_lastState != _state)
						cout << "STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET -- (TRANS_WORKER_NOT_WORKING_ON_DOOR) -- STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET" << endl;
					break;

				case TRANS_WORKER_DISPOSED_PART:
					if(_lastState != _state)
						cout << "STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET -- TRANS_WORKER_DISPOSED_PART -- STATE_HAND_EMPTY_NO_PART" << endl;
					_state = STATE_HAND_EMPTY_NO_PART;
					transitionSuccessful = true;
					personDiscardsPart(_partNo);	//Records time, resets timer
					break;
			}
			break;

		case STATE_WORKING_ON_DOOR:
			switch(stateTransition) {
				case TRANS_HANDOVER_COMPLETE:
					if(_lastState != _state)
						cout << "STATE_WORKING_ON_DOOR -- (TRANS_HANDOVER_COMPLETE) -- STATE_WORKING_ON_DOOR" << endl;
					break;

				case TRANS_WORKER_WORKING_ON_DOOR:
					if(_lastState != _state)
						cout << "STATE_WORKING_ON_DOOR -- (TRANS_WORKER_WORKING_ON_DOOR) -- STATE_WORKING_ON_DOOR" << endl;
					break;

				case TRANS_WORKER_NOT_WORKING_ON_DOOR:
					_state = STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR;
					transitionSuccessful = true;
					if(_lastState != _state)
						cout << "STATE_WORKING_ON_DOOR -- TRANS_WORKER_NOT_WORKING_ON_DOOR -- STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR" << endl;

					//Records time, resets timer
					personInstallsPart(_partNo);
					break;

				case TRANS_WORKER_DISPOSED_PART:
					if(_lastState != _state)
						cout << "STATE_WORKING_ON_DOOR -- (TRANS_WORKER_DISPOSED_PART) -- STATE_WORKING_ON_DOOR" << endl;
					personDiscardsPart(_partNo);	//Records time, resets timer
					break;
			}
			break;

		//HERE
		case STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR:
			switch(stateTransition) {
				case TRANS_HANDOVER_COMPLETE:
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR -- TRANS_HANDOVER_COMPLETE -- STATE_REMOVING_PART" << endl;
					_state = STATE_PART_IN_HAND_NOT_WORKING_ON_DOOR_YET;
					transitionSuccessful = true;
					_sw.resetAndStart();			//Reset timer
					break;
				case TRANS_WORKER_WORKING_ON_DOOR:
					_state = STATE_REMOVING_PART;
					transitionSuccessful = true;
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR -- TRANS_WORKER_WORKING_ON_DOOR -- STATE_REMOVING_PART" << endl;
					//NO OTHER ACTIONS REQUIRED
					break;
				case TRANS_WORKER_NOT_WORKING_ON_DOOR:
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR -- (TRANS_WORKER_NOT_WORKING_ON_DOOR) -- STATE_REMOVING_PART" << endl;
					break;
				case TRANS_WORKER_DISPOSED_PART:
					if(_lastState != _state)
						cout << "STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR -- (TRANS_WORKER_DISPOSED_PART) -- STATE_REMOVING_PART" << endl;
					personDiscardsPart(_partNo);	//Records time, resets timer
					break;
			}
			break;

		case STATE_REMOVING_PART:
			switch(stateTransition) {
				case TRANS_HANDOVER_COMPLETE:
					if(_lastState != _state)
						cout << "STATE_REMOVING_PART -- (STATE_REMOVING_PART) -- STATE_REMOVING_PART" << endl;
					break;
				case TRANS_WORKER_WORKING_ON_DOOR:
					if(_lastState != _state)
						cout << "STATE_REMOVING_PART -- (TRANS_WORKER_WORKING_ON_DOOR) -- STATE_REMOVING_PART" << endl;
					break;

				case TRANS_WORKER_NOT_WORKING_ON_DOOR:
					_state = START_PART_IN_HAND_HAS_REMOVED_PART;
					transitionSuccessful = true;

					if(_lastState != _state)
						cout << "MAGIC DISPOSAL STATE" << endl;
					//Records time, resets timer
					personRemovesInstalledPart(_partNo);
					sleep(1);
					personDiscardsPart(_partNo);
					break;

				case TRANS_WORKER_DISPOSED_PART:
					if(_lastState != _state)
						cout << "STATE_REMOVING_PART -- (TRANS_WORKER_DISPOSED_PART) -- STATE_REMOVING_PART" << endl;
					personDiscardsPart(_partNo);	//Records time, resets timer
					break;
			}
			break;

		case START_PART_IN_HAND_HAS_REMOVED_PART:
			switch(stateTransition) {
				case TRANS_HANDOVER_COMPLETE:
					if(_lastState != _state)
						cout << "START_PART_IN_HAND_HAS_REMOVED_PART -- (TRANS_HANDOVER_COMPLETE) -- START_PART_IN_HAND_HAS_REMOVED_PART" << endl;
					break;

				case TRANS_WORKER_WORKING_ON_DOOR:
					_state = STATE_WORKING_ON_DOOR;
					transitionSuccessful = true;
					//NO OTHER ACTIONS REQUIRED
					if(_lastState != _state)
						cout << "START_PART_IN_HAND_HAS_REMOVED_PART -- TRANS_WORKER_WORKING_ON_DOOR -- STATE_WORKING_ON_DOOR" << endl;
					break;

				case TRANS_WORKER_NOT_WORKING_ON_DOOR:
					if(_lastState != _state)
						cout << "START_PART_IN_HAND_HAS_REMOVED_PART -- (TRANS_WORKER_NOT_WORKING_ON_DOOR) -- START_PART_IN_HAND_HAS_REMOVED_PART" << endl;
					break;

				case TRANS_WORKER_DISPOSED_PART:
					_state = STATE_HAND_EMPTY_NO_PART;
					transitionSuccessful = true;
					if(_lastState != _state)
						cout << "START_PART_IN_HAND_HAS_REMOVED_PART -- TRANS_WORKER_DISPOSED_PART -- STATE_HAND_EMPTY_NO_PART" << endl;
					personDiscardsPart(_partNo);	//Records time, resets timer
					break;
			}
			break;
	}

	//if(!transitionSuccessful) abort();
	_lastState = _state;
}

void PFPerson::setPartNo(int partNo) {
	//cout << "PFPerson::setPartNo:	" << partNo << endl;
	_partNo = partNo;
}

void PFPerson::process(const CProtocol::tSMCPayload *payload) {
	//int a = payload->Conditions[CProtocol::WorkerWorkingOnDoor];
	//cout << "PFPerson::process:	" << a  << endl;
	if(payload->Conditions[CProtocol::WorkerWorkingOnDoor] ==
		CProtocol::eTRUE) {
		//cout << "PFPerson::process: WorkerWorkingOnDoor" << endl;
		//abort();
		transitionState(TRANS_WORKER_WORKING_ON_DOOR);
	} else if(payload->Conditions[CProtocol::WorkerNotWorkingOnDoor] ==
		CProtocol::eTRUE) {
		//cout << "PFPerson::process: WorkerNotWorkingOnDoor" << endl;
		transitionState(TRANS_WORKER_NOT_WORKING_ON_DOOR);
	} else if(payload->Conditions[CProtocol::WorkerDisposedPart] ==
		CProtocol::eTRUE) {
		cout << "PFPerson::process: WorkerDisposedPart" << endl;
		//transitionState(TRANS_WORKER_DISPOSED_PART);
		_state = STATE_HAND_EMPTY_HAS_WORKED_ON_DOOR;
		personDiscardsPart(_partNo);	//Records time, resets timer
	}
}

/*
	(:action personInstallsPart
		:parameters	(
						?theperson		-	person
						?thepart		-	part
						?thedestination	-	partdestination
						?theparttype	-	parttype
					)
	)
*/

void PFPerson::personInstallsPart(int partNo) {
	vector<string> params;
	params.push_back("per1");
	params.push_back(_m[partNo]->_thepart);
	params.push_back(_m[partNo]->_thedestination);
	params.push_back(_m[partNo]->_theparttype);

	ParamList *pl = _plt.getPL("personInstallsPart", params);
	//cout << "PFPerson::personInstallsPart" << endl;
	cout << "PFPerson::personInstallsPart:	" << partNo << ":	";
	pl->printContents(true);
	pl->addTime(_sw.lap());			//Record time
	_sw.resetAndStart();			//Reset timer
	_wm.apply(*pl);
}

/*
	(:action personRemovesInstalledPart
		:parameters	(
						?thepart		-	part
						?thedestination	-	partdestination
						?theperson		-	person
					)
	)
*/

void PFPerson::personRemovesInstalledPart(int partNo) {
	vector<string> params;
	params.push_back(_m[partNo]->_thepart);
	params.push_back(_m[partNo]->_thedestination);
	params.push_back("per1");

	ParamList *pl = _plt.getPL("personRemovesInstalledPart", params);
	cout << "PFPerson::personRemovesInstalledPart:	" << partNo << ":	";
	pl->printContents(true);
	pl->addTime(_sw.lap());			//Record time
	_sw.resetAndStart();			//Reset timer
	_wm.apply(*pl);
}

/*
	(:action personDiscardsPart
		:parameters	(
						?thepart		-	part
						?theperson		-	person
					)
	)	
*/
void PFPerson::personDiscardsPart(int partNo) {	//Records time, resets timer
	vector<string> params;
	string partParam = _m[partNo]->_thepart;
	params.push_back(partParam);
	params.push_back(_m[partNo]->_theparttype);
	params.push_back("per1");
	params.push_back(_m[partNo]->_nullpart);
	params.push_back(_m[partNo]->_nullparttype);

	ParamList *pl = _plt.getPL("personDiscardsPart", params);
	cout << "PFPerson::personDiscardsPart:	" << partNo << ":	";
	pl->printContents(true);
	pl->addTime(_sw.lap());			//Record time
	_sw.resetAndStart();			//Reset timer
	_wm.apply(*pl);
}

PFPerson::PartInfo::PartInfo(string thepart, string thedestination,
	string theparttype) : _thepart(thepart), _thedestination(thedestination),
	_theparttype(theparttype),
	_nullpart("p5"),
	_nullparttype("PTYPENULL") {}

PFPerson::PartInfo::~PartInfo() {}
