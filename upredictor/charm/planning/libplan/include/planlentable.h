#ifndef PLAN_LEN_TABLE_H
#define PLAN_LEN_TABLE_H

#include <map>
#include <vector>

using namespace std;

class Plan;
class PlanTable;

class PlanLenTable {
	public:
		PlanLenTable();
		~PlanLenTable();

		void clear();
		void compile(PlanTable &pt);

		Plan &getFirst();

		int size();

	protected:
		map<int, vector<Plan *> > _m;
};

#endif
