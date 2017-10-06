#ifndef CONCURRENT_PLAN_TABLE_H
#define CONCURRENT_PLAN_TABLE_H

#include "concurrentactiontable.h"

#include <vector>

using namespace std;

class ConcurrentPlan;
class PlanTable;

class ConcurrentPlanTable {
	public:
		ConcurrentPlanTable();
		~ConcurrentPlanTable();

		int getNumberConcurrentPlans();
		ConcurrentPlan &getConcurrentPlan(int index);

		void clear();

		void populate(PlanTable &plans);

	protected:
		ConcurrentActionTable _cat;
		vector<ConcurrentPlan *> _concurrentPlans;
};

#endif
