#include "worldmodel.h"
#include "paramlist.h"
#include "paramlisttable.h"

#include <iostream>

WorldModel::WorldModel(PlanState *ps, ParamListTable &plt) :
	_ps(ps), _plt(plt) {
	pthread_mutex_init(&_mut, NULL);
	sem_init(&_sem, 0, 0);
	//_ps.printContents();
}

WorldModel::~WorldModel() {}

vector<ParamList *> WorldModel::computeApplicablePL() {
	vector<ParamList *> applicablePL;

	pthread_mutex_lock(&_mut);
	for(int i = 0; i < _plt.size(); i++) {
		ParamList &pl = _plt.getPL(i);
		if(_ps.preconditionsMet(pl))
			applicablePL.push_back(&pl);
	}
	pthread_mutex_unlock(&_mut);

	return applicablePL;
}

void WorldModel::apply(ParamList &pl) {
	pthread_mutex_lock(&_mut);
	pl.applyToPlanState(&_ps);
	sem_post(&_sem);
	pthread_mutex_unlock(&_mut);
}

void WorldModel::waitForThis(ParamList &pl) {
	bool waiting = true;
	while(waiting) {
		cout << "WorldModel::waitForThis: WAITING" << endl;
		sem_wait(&_sem);
		cout << "WorldModel::waitForThis: TESTING" << endl;
		pthread_mutex_lock(&_mut);
		waiting = !_ps.postConditionsMet(pl);
		pthread_mutex_unlock(&_mut);
		cout << "WorldModel::waitForThis: WAIT:	" << waiting << endl;
	}	
}

void WorldModel::waitForUpdate() {
	sem_wait(&_sem);
}

PlanState *WorldModel::getCurrentState() {
	return &_ps;
}

ParamListTable &WorldModel::getPLT() {
	return _plt;
}
