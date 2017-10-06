#ifndef CONCURRENT_ACTION_TABLE_H
#define CONCURRENT_ACTION_TABLE_H

#include <map>

using namespace std;

class ConcurrentPlanAction;
class ParamList;

class ConcurrentActionTable {
	public:
		ConcurrentActionTable();
		~ConcurrentActionTable();

		ConcurrentPlanAction *getPlanStep(ParamList &pl);

	protected:
		map<int, ConcurrentPlanAction *> _actions;
};

#endif
