#ifndef CONCURRENT_PLAN_H
#define CONCURRENT_PLAN_H

#include <set>
#include <vector>

using namespace std;

class ConcurrentActionTable;
class ConcurrentPlan;
class ConcurrentPlanConcurrency;
class ConcurrentPlanGrid;
class ParamList;
class ParamListTable;
class PlanningGraph;
class Plan;
class PlanState;
class PlanStateTable;
class PlanTable;

class ConcurrentPlan {
	public:	
		static void populatePlans(PlanTable &pt,
			vector<ConcurrentPlan *> &finished, ConcurrentActionTable &cat);

		ConcurrentPlan(Plan *plan, ConcurrentActionTable &cat);
		~ConcurrentPlan();

		int insertNextPlanState(vector<ConcurrentPlan *> &inProgress);
		bool hasNextInsertion();

		ParamListTable &getPLT();
		ConcurrentActionTable &getCAT();

		//void printContents();

		void printContents(int actionSpaces, int lineNumber,
			bool cr = true, int digitsForAction = 3);
		void printGrid();
		int getNTimeSteps();
		void label();

		Plan &getPlan();

		double computePerformanceTime();
		double getPerformanceTime();

		int computeStepLen();
		int getStepLen();

		ConcurrentPlanGrid *generateGrid();

		int _status;

	protected:
		int insert(int paramList, vector<ConcurrentPlan *> &inProgress);

		Plan *_plan;
		ConcurrentActionTable &_cat;
		PlanningGraph &_pg;
		ParamListTable &_plt;
		PlanStateTable &_pst;
		int _currentInsertion;

		ConcurrentPlanConcurrency *_concurrency;
		bool _crazyCakes;
};

#endif
