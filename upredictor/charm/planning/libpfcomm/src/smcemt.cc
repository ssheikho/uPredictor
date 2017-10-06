#include "smcemt.h"
#include "paramlist.h"
#include "paramlisttable.h"
#include "smcgetpartevent.h"
#include "smcmovetopersonevent.h"
#include "smcmovebackevent.h"
#include "smcstarthandoverevent.h"


#include <cstring>
#include <fstream>
#include <iostream>

SMCEMT::SMCEMT(ParamListTable &plt, WorldModel *wm, SMCConnection &smcc,
	PFPerson &person, bool liveFire) :
	_plt(plt), _wm(wm), _smcc(smcc), _person(person), _liveFire(liveFire) {}
SMCEMT::~SMCEMT() {}

SMCEventModel *SMCEMT::getEM(ParamList *pl) {
	cout << "SMCEMT::getEM" << endl;
	int plInd = pl->getIndex();
	int emInd = _m[plInd];
	SMCEventModel *em = _v[emInd];
	pl->printContents(true);
	return em;
}

void SMCEMT::load(string filename) {
	map<string, string> m;

	fstream in(filename.c_str());
	while(!in.eof()) {
		string action, eventmodel;
		in >> action;
		in >> eventmodel;
		m[action] = eventmodel;
	}

	for(int i = 0; i < _plt.size(); i++) {
		ParamList &pl = _plt.getPL(i);
		string name = pl.getAction().getName();
		SMCEventModel *em = NULL;
		if(m.find(name) != m.end()) {
			string eventmodel = m[name];

			if(strcmp(eventmodel.c_str(), "smcmovebackevent") == 0) {
				em = new SMCMoveBackEvent(&pl, _wm, _smcc, _liveFire);
			} else if(strcmp(eventmodel.c_str(), "smcstarthandoverevent") ==
				0) {
				em = new SMCStartHandoverEvent(&pl, _wm, _smcc, _person,
					_liveFire);
			} else if(strcmp(eventmodel.c_str(), "smcgetpartevent") == 0) {
				em = new SMCGetPartEvent(&pl, _wm, _smcc, _liveFire);
			} else if(strcmp(eventmodel.c_str(), "smcmovetopersonevent") == 0) {
				em = new SMCMoveToPersonEvent(&pl, _wm, _smcc, _liveFire);
			}

			_m[pl.getIndex()] = _v.size();
			_v.push_back(em);
		}
	}

		/*
		vector<ParamList *> pl = _plt.getPLForAction(action);

		if(strcmp(eventmodel.c_str(), "smcmovebackevent") == 0) {
			for(int i = 0; i < pl.size(); i++) {
				_m[pl[i]->getIndex()] = _v.size();
				_v.push_back(new SMCMoveBackEvent(pl[i]));
			}
		} else if(strcmp(eventmodel.c_str(), "smcstarthandoverevent") == 0) {
			cout << "SMCEMT::load:	" << action << "	" << eventmodel << endl;
			for(int i = 0; i < pl.size(); i++) {
				_m[pl[i]->getIndex()] = _v.size();
				_v.push_back(new SMCStartHandoverEvent(pl[i]));
			}
		} else if(strcmp(eventmodel.c_str(), "smcgetpartevent") == 0) {
			int plSize = pl.size();
			cout << "SMCEMT::load:	" << action << "	" << eventmodel <<
				"	" << plSize << endl;
			for(int i = 0; i < plSize; i++) {
				ParamList *p = pl[i];
				_m[p->getIndex()] = _v.size();
				_v.push_back(new SMCGetPartEvent(p));
			}
		} else if(strcmp(eventmodel.c_str(), "smcmovetopersonevent") == 0) {
			for(int i = 0; i < pl.size(); i++) {
				_m[pl[i]->getIndex()] = _v.size();
				_v.push_back(new SMCMoveToPersonEvent(pl[i]));
			}
		}
	}
	*/
}
