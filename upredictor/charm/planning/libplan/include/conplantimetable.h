#ifndef CON_PLAN_TIME_TABLE_H
#define CON_PLAN_TIME_TABLE_H

#include <map>

using namespace std;

class ConcurrentPlan;
class ConcurrentPlanTable;
class ConPlanLenTable;

class ConPlanTimeTable {
	public:
		ConPlanTimeTable(ConcurrentPlanTable &cpt);
		~ConPlanTimeTable();

		void clear();
		void update();

		ConcurrentPlan *getFirst();

	protected:
		ConcurrentPlanTable &_cpt;
		map<double, ConPlanLenTable *> _m;
};

#endif
