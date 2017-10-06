#ifndef ACTION_TO_ACTOR_H
#define ACTION_TO_ACTOR_H

#include "actionexecutor.h"

#include <map>
#include <string>

using namespace std;

class ActionMap;
class ActorTable;

/*
	Really, actor an executor should be separated.  A planner that does not
		concern itself with plan execution should not be burdened with it.
		This is a concern for later work, if this ever comes up.
*/

class ActionToActor : public ActionExecutor {
	public:
		ActionToActor(ActionMap &am, ActorTable *at);
		~ActionToActor();

		void registerAction(int actor, string action);
	
		void execute(ParamList *pl);

	protected:
		ActionMap &_am;
		ActorTable *_at;
		map<int, int> _m;
};

#endif
