#include "smcresponseactor.h"
#include "actiontoactor.h"
#include "paramlist.h"
#include "smcconnection.h"
#include "smcemt.h"
#include "smceventmodel.h"

#include <algorithm>
#include <iostream>

using namespace std;

SMCResponseActor::SMCResponseActor(string name, int id, ActionToActor &ata,
	WorldModel &wm, SMCEMT &emt, SMCConnection &smc) :
	Actor(name, id, ata, wm), _emt(emt) {
	pthread_mutex_init(&_mut, NULL);
	smc.addMessageHandler(this);
}

SMCResponseActor::~SMCResponseActor() {}

void SMCResponseActor::execute(ParamList *pl) {
	pthread_mutex_lock(&_mut);

	cout << "ACTOR:	TYPE:	SMCResponseActor	" << _name << "	EXECUTING:	";
	pl->printContents(true);

	SMCEventModel *em = _emt.getEM(pl);
	em->start();
	_eventModels.push_back(em);

	pthread_mutex_unlock(&_mut);
}

void SMCResponseActor::configure() {
	//cout << "ACTOR:	TYPE:	SMCResponseActor	" << _name << "	CONFIGURING";
}

void SMCResponseActor::process(const CProtocol::tSMCPayload *payload) {
	pthread_mutex_lock(&_mut);
	vector<SMCEventModel *> toRemove;
	for(int i = 0; i  < _eventModels.size(); i++) {
		_eventModels[i]->process(payload);
		if(_eventModels[i]->isDone()) {
			toRemove.push_back(_eventModels[i]);
		}
	}
	for(int i = 0; i < toRemove.size(); i++) {
		vector<SMCEventModel *> ::iterator j =
			find(_eventModels.begin(), _eventModels.end(), toRemove[i]);
		_eventModels.erase(j);
	}

	/*
	for(int i = 0; i  < toRemove.size(); i++) {
		bool done = false;
		for(vector<SMCEventModel *>::iterator j = toRemove.begin();
			((!done) && (j != toRemove.end())); j++) {
			if(toRemove[i] == *j) {
				_eventModels.erase(j);
				done = true;
			}
		}
	}
	*/
	pthread_mutex_unlock(&_mut);
}
