#ifndef PLAN_RESPONDER_H
#define PLAN_RESPONDER_H

#include <pthread.h>

class ActionExecutor;
class ConcurrentPlan;
class ConcurrentPlanGrid;
class ConcurrentReplanner;
class ParamList;
class ParamListTable;
class PlanLenTable;
class PlanningGraph;
class WhenPlanDone;
class WorldModel;

class ConcurrentPlanResponder {
	public:
		static void *prThread(void *in);

		ConcurrentPlanResponder(ConcurrentReplanner &replanner, WorldModel &wm,
			ActionExecutor &ae, WhenPlanDone *wpd = NULL);
		~ConcurrentPlanResponder();
	
		int update();
		void sendNextInstructions();

		void startThread();
		void waitThread();

	protected:
		ConcurrentReplanner &_replanner;
		WorldModel &_wm;
		ActionExecutor &_ae;
		WhenPlanDone *_wpd;
		ConcurrentPlan *_cp;
		ConcurrentPlanGrid *_cpg;
		PlanLenTable *_plt;
		PlanningGraph *_pg;
		ParamListTable *_paramListTable;
		pthread_t _thread;
};

#endif
