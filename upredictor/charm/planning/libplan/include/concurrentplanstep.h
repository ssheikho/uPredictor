#ifndef CONCURRENT_PLAN_STEP_H
#define CONCURRENT_PLAN_STEP_H

#include <string>
#include <vector>

using namespace std;

class ConcurrentPlan;
class ConcurrentPlanGrid;
class ConcurrentPlanStep;
class ParamList;
class PlanState;

typedef ConcurrentPlanStep *ConcurrentPlanStepPtr;
typedef ConcurrentPlanStepPtr *ConcurrentPlanStepPtrPtr;
typedef ConcurrentPlanStepPtrPtr *ConcurrentPlanStepPtrPtrPtr;

class ConcurrentPlanStep {
	public:
		enum {
			INSERT_STATUS_NOT_INSERTED,
			INSERT_STATUS_INSERTED,
			INSERT_STATUS_SKIP,
			INSERT_STATUS_INSERT_AT_END
		};

		ConcurrentPlanStep();
		~ConcurrentPlanStep();

		enum CPSType{action, line, concurrency};

		ConcurrentPlanGrid *generateGrid();
		void printGrid();
		double getPerformanceTime();
		int getStepLen();

		virtual int attemptInsertion(
			ParamList &pl, vector<ConcurrentPlan *> &inProgress) = 0;
		virtual void applyToPlanState(PlanState *state) = 0;
		virtual PlanState *doStep(PlanState *state) = 0;
		virtual bool doesntInterfere(ParamList &pl) = 0;

		virtual int getType() = 0;

		virtual int getNTimeSteps() = 0;
		virtual int getNTotalTimelines() = 0;

		virtual void printContents(int actionSpaces, int lineNumber,
			bool cr = true, int digitsForAction = 3) = 0;

		virtual pair<int, int> fillInPlanMat(
			ConcurrentPlanStepPtr **steps, int startRow, int startCol) = 0;
		virtual void fillInPlanMatTwo(ConcurrentPlanStepPtr **steps) = 0;

		virtual string getString() = 0;

		virtual pair<int, int> label(int startRow, int startCol,
			int printTabs) = 0;

		virtual double computePerformanceTime() = 0;
		virtual int computeStepLen() = 0;

		virtual bool isAPL() = 0;
		virtual ParamList *getPL() = 0;

	protected:
		pair<int, int> _stepNumber;
		double _timeToPerform;
		int _stepLen;
};

#endif
