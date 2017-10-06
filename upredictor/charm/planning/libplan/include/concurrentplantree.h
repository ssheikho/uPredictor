#ifndef CONCURRENT_PLAN_TREE_H
#define CONCURRENT_PLAN_TREE_H

#include <map>
#include <set>
#include <vector>

using namespace std;

class ParamListTable;
class PlanTree;

class ConcurrentPlanTree {
	public:
		ConcurrentPlanTree(PlanTree *pt,
			ConcurrentPlanTree *parent, ParamListTable &plt);
		~ConcurrentPlanTree();

	protected:
		void insert(PlanTree *pt);

		ConcurrentPlanTree *_parent;
		ParamListTable &_plt;
};

#endif
