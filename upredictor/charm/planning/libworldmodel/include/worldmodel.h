#ifndef WORLD_MODEL_H
#define WORLD_MODEL_H

#include "planstate.h"

#include <pthread.h>
#include <semaphore.h>

#include <vector>

using namespace std;

class ParamList;
class ParamListTable;

class WorldModel {
	public:
		WorldModel(PlanState *ps, ParamListTable &plt);
		~WorldModel();

		vector<ParamList *> computeApplicablePL();

		void apply(ParamList &pl);
		void waitForThis(ParamList &pl);
		void waitForUpdate();

		PlanState *getCurrentState();
		ParamListTable &getPLT();

	protected:
		PlanState _ps;
		ParamListTable &_plt;

		pthread_mutex_t _mut;
		sem_t _sem;
};

#endif
