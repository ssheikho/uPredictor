#ifndef SERIAL_PLAN_H
#define SERIAL_PLAN_H

#include <vector>

using namespace std;

class PlanningGraph;

class SerialPlan {
	public:
		SerialPlan(vector<int> &plan, vector<int> &edges, PlanningGraph &pg);
		~SerialPlan();

		void printContents();

		bool equals(Plan &p);
		int getParamList(int index);
		int getState(int index);
		int getNStates();

		PlanningGraph &getPlanningGraph();

	protected:
		int _nStates, *_plan, *_edges;
		PlanningGraph &_pg;
};

#endif
