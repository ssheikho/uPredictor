#ifndef PLANNING_GRAPH_H
#define PLANNING_GRAPH_H

#include "actionpredicate.h"
#include "paramlisttable.h"
#include "planstatetable.h"
#include "plantable.h"
#include "plantree.h"
#include "stopwatch.h"

#include <map>
#include <set>
#include <vector>

using namespace std;

class ParamList;
class Plan;
class PlanState;
class Problem;

class PlanningGraph {
	public:
		PlanningGraph(Problem *problem);
		~PlanningGraph();

		void printGoalStates();
		void printSummary();

		PlanTable &getPlans();
		ParamListTable &getPLT();
		PlanStateTable &getPST();

		PlanState *transition(PlanState *from, ParamList *link, bool &isNew);

		void printBackMatrix();
	
		void doPlanning(PlanState *fromState = NULL);

	protected:
		void expandOneLevel(bool ignoreNot);
		void identifyGoalStates();
		void compilePlans();
		void compilePlans(vector<int> &plan, vector<int> &edges, int fromState);
		bool vectorContains(vector<int> &plan, int state);

		Problem *_problem;

		vector<PlanState *> _ready, _goals;
		ParamListTable _plt;
		PlanStateTable _pst;

		map<int, map<int, int> > _forwardLinks;
		map<int, map<int, int> > _forwardAcrossActions;
		map<int, set<int> > _backLinks;
		
		PlanTable _plans;
		//PlanTree _planTree;

		int _rootState;

		StopWatch _sw;
};

#endif
