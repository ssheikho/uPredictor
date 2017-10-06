#include "concurrentplantree.h"
#include "plantree.h"

ConcurrentPlanTree::ConcurrentPlanTree(PlanTree *pt,
	ConcurrentPlanTree *parent, ParamListTable &plt) :
	_parent(parent), _plt(plt) {
}

ConcurrentPlanTree::~ConcurrentPlanTree() {}

void ConcurrentPlanTree::insert(PlanTree *pt) {
	
}
