#ifndef PLAN_TABLE_H
#define PLAN_TABLE_H

#include <vector>

using namespace std;

class Plan;

class PlanTable {
	public:
		PlanTable();
		~PlanTable();

		bool insert(Plan *p, bool checkEquiv, bool checkCycle = false);
		Plan &get(int index);
		int size();

		void printPlans(int limit = -1);

		void clear();

	protected:
		vector<Plan *> _v;
};

#endif
