#ifndef CONCURRENT_PLAN_LINE_H
#define CONCURRENT_PLAN_LINE_H

#include "concurrentplanstep.h"
#include "planstate.h"

#include <vector>

using namespace std;

class ConcurrentActionTable;
class ConcurrentPlan;
class ParamList;
class PlanState;

class ConcurrentPlanLine : public ConcurrentPlanStep {
	public:
		ConcurrentPlanLine(ConcurrentPlan *cp, PlanState *rootState);
		~ConcurrentPlanLine();
		
		bool actionCanBeAddedToEnd(ParamList &pl);
		bool actionCanBeAppliedBeforeLast(ParamList &pl);

		void addParamList(ParamList &pl);
		void addPlanStep(ConcurrentPlanStep *cps);
		void splitLastWithThis(ParamList &pl);

		int attemptInsertion(
			ParamList &pl, vector<ConcurrentPlan *> &inProgress);
		void applyToPlanState(PlanState *state);
		PlanState *doStep(PlanState *state);
		int getType();
		void printContents(int actionSpaces, int lineNumber,
			bool cr = true, int digitsForAction = 3);
		int getNTimeSteps();
		int getNTotalTimelines();

		bool doesntInterfere(ParamList &pl);

		pair<int, int> fillInPlanMat(
			ConcurrentPlanStep ***steps, int startRow, int startCol);
		void fillInPlanMatTwo(ConcurrentPlanStepPtr **steps);

		string getString();

		double computePerformanceTime();
		int computeStepLen();

		pair<int, int> label(int startRow, int startCol, int printTabs);

		bool isAPL();
		ParamList *getPL();
		
	protected:
		void addPlanStep(ConcurrentPlanStep *cps, PlanState *state);

		//vector<int> _paramLists;
		ConcurrentPlan *_cp;
		vector<ConcurrentPlanStep *> _pls;
		vector<PlanState *> _states;
		//vector<int> _states;
		bool _weAppendIntoLastNow;
};

#endif
