#ifndef REPLANNER_H
#define REPLANNER_H

#include "stopwatch.h"

class PlanState;
class Problem;

class Replanner {
	public:
		Replanner(Problem &problem);
		~Replanner();

		void replan(bool showTimes, PlanState *fromState = NULL);

		Problem &getProblem();

	protected:
		Problem &_problem;
		StopWatch _sw;
};

#endif
