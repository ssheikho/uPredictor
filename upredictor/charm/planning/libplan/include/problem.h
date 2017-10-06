#ifndef PROBLEM_H
#define PROBLEM_H

#include "objecttable.h"
#include "planstate.h"
#include "planstatepredtable.h"
#include <string>

using namespace std;

class Domain;
class PlanningGraph;

class Problem {
	public:
		Problem(Domain &domain, string name);
		~Problem();

		string getName();
		
		Domain &getDomain();
		ObjectTable &getObjectTable();
		PlanStatePredTable &getPSPT();

		void generatePG();
		PlanningGraph &getPG();

		PlanState &getRootState();
		PlanState &getGoalState();
		
	protected:
		Domain &_domain;
		string _name;
		ObjectTable _objectTable;
		PlanStatePredTable _pspt;
		PlanningGraph *_pg;
		PlanState *_rootState, _goalState;
};

#endif
