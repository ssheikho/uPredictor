#ifndef WHEN_PLAN_DONE_H
#define WHEN_PLAN_DONE_H

class WhenPlanDone {
	public:
		WhenPlanDone();
		~WhenPlanDone();
		
		virtual void onCompletion() = 0;
};

#endif
