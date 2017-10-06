#ifndef PLAN_RESPONDER_H
#define PLAN_RESPONDER_H

#include <pthread.h>

class ActionExecutor;
class ParamList;
class ParamListTable;
class PlanLenTable;
class PlanningGraph;
class Replanner;
class WhenPlanDone;
class WorldModel;

class PlanResponder {
	public:
		static void *prThread(void *in);

		PlanResponder(Replanner &replanner, WorldModel &wm, ActionExecutor &ae,
			WhenPlanDone *wpd = NULL);
		~PlanResponder();
	
		ParamList *getNextInstruction();
		void sendNextInstruction();

		void startThread();
		void waitThread();

	protected:
		Replanner &_replanner;
		WorldModel &_wm;
		ActionExecutor &_ae;
		WhenPlanDone *_wpd;
		PlanLenTable *_plt;
		PlanningGraph *_pg;
		ParamListTable *_paramListTable;
		pthread_t _thread;
};

#endif
