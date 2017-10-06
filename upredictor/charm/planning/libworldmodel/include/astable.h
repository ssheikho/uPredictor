#ifndef AS_TABLE_H
#define AS_TABLE_H

#include "stopwatch.h"

#include <vector>

using namespace std;

class ActorPlan;
class ActorSorter;
class ConcurrentPlanTable;
class PlanTable;
class WorldModel;

class ASTable {
	public:
		ASTable(ActorSorter &as, WorldModel &wm);
		~ASTable();
	
		void clear();
		void update(PlanTable &pt);
		//void update(ConcurrentPlanTable &pt);

		ActorPlan *getPlan(int index);
		int getNumPlans();

		void insertOrDelete(ActorPlan *ap);

	protected:
		ActorSorter &_as;
		WorldModel &_wm;
		vector<ActorPlan *> _v;
		StopWatch _sw;
};

#endif
