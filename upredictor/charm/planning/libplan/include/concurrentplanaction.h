#ifndef CONCURRENT_PLAN_ACTION_H
#define CONCURRENT_PLAN_ACTION_H

#include "concurrentplanstep.h"

class ParamList;
class PlanState;

class ConcurrentPlanAction : public ConcurrentPlanStep {
	public:
		ConcurrentPlanAction(ParamList &pl);
		~ConcurrentPlanAction();

		PlanState *doAction(PlanState *to);

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
		ParamList &_pl;
};

#endif
