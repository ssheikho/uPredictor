#ifndef SUB_PLAN_H
#define SUB_PLAN_H

class Plan;

class SubPlan {
	public:
		SubPlan(Plan *plan, int startStep, int endStep);
		~SubPlan();

		int getState(int index);
		int getNStates();

	protected:
		Plan *_plan;
		int _startStep, _endStep;
};

#endif
