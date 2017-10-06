#ifndef CONCURRENT_REPLANNER_H
#define CONCURRENT_REPLANNER_H

#include "concurrentplantable.h"
#include "conplantimetable.h"
#include "stopwatch.h"

class PlanState;
class Problem;

class ConcurrentReplanner {
	public:
		ConcurrentReplanner(Problem &problem);
		~ConcurrentReplanner();

		void replan(bool showTimes, PlanState *fromState = NULL);

		Problem &getProblem();
		ConcurrentPlanTable &getCPT();
		ConPlanTimeTable &getCPTT();

	protected:
		Problem &_problem;
		ConcurrentPlanTable _cpt;
		ConPlanTimeTable _cptt;
		StopWatch _sw;
};

#endif
