#ifndef PRINT_ACTOR_H
#define PRINT_ACTOR_H

#include "actor.h"

using namespace std;

class PrintActor : public Actor {
	public:
		PrintActor(string name, int id, ActionToActor &ata, WorldModel &wm);
		~PrintActor();
	
		void execute(ParamList *pl);
		void configure();
};

#endif
