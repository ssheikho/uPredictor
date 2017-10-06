#ifndef AUTO_ACTOR_H
#define AUTO_ACTOR_H

#include "actor.h"

class AutoActor : public Actor {
	public:
		AutoActor(string name, int id, ActionToActor &ata, WorldModel &wm);
		~AutoActor();

		void execute(ParamList *pl);
		void configure();
};

#endif
