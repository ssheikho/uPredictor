#ifndef SMC_RESPONSE_ACTOR_H
#define SMC_RESPONSE_ACTOR_H

#include "actor.h"
#include "smcmessagehandler.h"

#include <pthread.h>

#include <vector>

using namespace std;

class ActionToActor;
class ParamList;
class SMCConnection;
class SMCEMT;
class SMCEventModel;
class WorldModel;

class SMCResponseActor : public Actor, public SMCMessageHandler {
	public:
		SMCResponseActor(string name, int id, ActionToActor &ata,
			WorldModel &wm, SMCEMT &emt, SMCConnection &smc);
		~SMCResponseActor();
	
		void execute(ParamList *pl);
		void configure();

		void process(const CProtocol::tSMCPayload *payload);

	protected:
		SMCEMT &_emt;
		//SMCConnection &_smc;
		vector<SMCEventModel *> _eventModels;

		pthread_mutex_t _mut;
};

#endif
