#include "concurrentactiontable.h"
#include "concurrentplanaction.h"
#include "paramlist.h"

#include <cstdlib>

ConcurrentActionTable::ConcurrentActionTable() {}
ConcurrentActionTable::~ConcurrentActionTable() {}

ConcurrentPlanAction *ConcurrentActionTable::getPlanStep(ParamList &pl) {
	if(_actions.find(pl.getIndex()) == _actions.end())
		_actions[pl.getIndex()] = new ConcurrentPlanAction(pl);

	return _actions[pl.getIndex()];
}
