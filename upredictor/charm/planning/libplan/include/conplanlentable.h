#ifndef CON_PLAN_LEN_TABLE_H
#define CON_PLAN_LEN_TABLE_H

#include <map>
#include <vector>

using namespace std;

class ConcurrentPlan;

class ConPlanLenTable {
	public:
		ConPlanLenTable();
		~ConPlanLenTable();

		void clear();
		void insert(ConcurrentPlan *p);

		ConcurrentPlan *getFirst();

	protected:
		map<int, vector<ConcurrentPlan *> > _m;
};

#endif
