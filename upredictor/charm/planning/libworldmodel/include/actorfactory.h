#ifndef ACTOR_FACTORY_H
#define ACTOR_FACTORY_H

#include <string>

using namespace std;

class ActionToActor;
class Actor;
class WorldModel;

class ActorFactory {
	public:
		ActorFactory(WorldModel &wm);
		~ActorFactory();

		Actor *getActor(ActionToActor &ata, string name, int id, string type,
			string configfile); 

	protected:
		WorldModel &_wm;
};

/*
	//, SMCEMT &emt, SMCConnection &smc, PFPerson &person

	class PFPerson;
	class SMCConnection;
	class SMCEMT;

	SMCEMT &_emt;
	SMCConnection &_smc;
	PFPerson &_person;
*/

#endif
