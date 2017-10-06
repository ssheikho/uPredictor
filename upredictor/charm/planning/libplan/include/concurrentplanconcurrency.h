#ifndef CONCURRENT_PLAN_CONCURRENCY_H
#define CONCURRENT_PLAN_CONCURRENCY_H

#include "concurrentplanstep.h"

#include <set>
#include <vector>

using namespace std;

class ConcurrentActionTable;
class ConcurrentPlan;
class ConcurrentPlanLine;
class ParamList;
class PlanState;

class ConcurrentPlanConcurrency : public ConcurrentPlanStep {
	public:
		ConcurrentPlanConcurrency(
			ConcurrentPlan *cp, PlanState *rootState,
			bool seedOneTimeline = true);
		~ConcurrentPlanConcurrency();

		ConcurrentPlanLine *addTimeline();
		ConcurrentPlanLine *getTimeline(int index);
		int getNumTimelines();

		int getNumApplicableTimelines(ParamList &pl);
		vector<ConcurrentPlanLine *> getApplicableTimelines(ParamList &pl);
		//int getNumCompatibleTimelines();

		//JWH	Returns false if insertion is impossible
		int insert(int paramList, vector<ConcurrentPlan *> &inProgress);

		int attemptInsertion(
			ParamList &pl, vector<ConcurrentPlan *> &inProgress);
		void applyToPlanState(PlanState *state);
		PlanState *doStep(PlanState *state);
		int getType();
		int getNTimeSteps();
		bool doesntInterfere(ParamList &pl);

		void printContents(int actionSpaces, int lineNumber,
			bool cr = true, int digitsForAction = 3);

		int getNTotalTimelines();

		PlanState *getRootState();
	
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
		bool applicableToRootState(ParamList &pl);
		int insertNotAtRoot(
			ParamList &pl, vector<ConcurrentPlan *> &inProgress);
		bool applicableAtEndOfCombo(ParamList &pl, set<int> &in);
		void applyToPlanState(PlanState *state, set<int> &in);
		PlanState *doStep(PlanState *state, set<int> &in);

		vector<set<int> > tryAllCombos(ParamList &pl, int in);
		bool setIsInVectorLeft(
			vector<pair<set<int>, set<int> > > &v, set<int> &in);

		ConcurrentPlan *_cp;
		PlanState *_rootState;
		vector<ConcurrentPlanLine *> _timeLines;
};

#endif
