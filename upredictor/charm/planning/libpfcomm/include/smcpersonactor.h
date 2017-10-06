#ifndef SMC_PERSON_ACTOR_H
#define SMC_PERSON_ACTOR_H

#include "actor.h"

class PFPerson;

class SMCPersonActor : public Actor {
	public:
		SMCPersonActor(PFPerson &person, string name, int id,
			ActionToActor &ata, WorldModel &wm);
		~SMCPersonActor();
	
		void execute(ParamList *pl);
		void configure();

	protected:		
		PFPerson &_person;
};

#endif
