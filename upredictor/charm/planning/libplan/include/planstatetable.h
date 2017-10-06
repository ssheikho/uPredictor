#ifndef PLAN_STATE_TABLE_H
#define PLAN_STATE_TABLE_H

#include <vector>

using namespace std;

class PlanState;

class PlanStateTable {
	public:
		PlanStateTable();
		~PlanStateTable();

		int stateExists(PlanState &p);
		int addCopyOrReturnExisting(PlanState *p);
		int addOrReturnExistingAndDelete(PlanState *p);
		int add(PlanState *p);
		int getNumStates();
		PlanState &getState(int index);

		void printStates();

	protected:
		int _stateCtr;
		vector<PlanState *> _committed;
};

#endif
