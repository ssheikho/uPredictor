#ifndef PLAN_H
#define PLAN_H

#include <vector>

using namespace std;

class PlanningGraph;

class Plan {
	public:
		Plan(vector<int> &plan, vector<int> &edges, PlanningGraph &pg);
		~Plan();

		void printContents();

		bool equals(Plan &p);
		int getParamList(int index);
		int getState(int index);
		int getNStates();

		PlanningGraph &getPlanningGraph();

		bool planHasACycle();

	protected:
		int _nStates, *_plan, *_edges;
		PlanningGraph &_pg;
};

#endif
