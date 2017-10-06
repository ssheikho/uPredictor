#ifndef SMC_START_HANDOVER_EVENT_H
#define SMC_START_HANDOVER_EVENT_H

#include "smceventmodel.h"

class PFPerson;

class SMCStartHandoverEvent : public SMCEventModel {
	public:
		SMCStartHandoverEvent(ParamList *pl, WorldModel *wm,
			SMCConnection &smcc, PFPerson &person, bool liveFire);
		~SMCStartHandoverEvent();

		void process(const CProtocol::tSMCPayload *payload);
		bool isDone();
		void start();

	protected:
		enum {
			STATE_NULL,
			STATE_START,
			STATE_INTERMEDIATE,
			STATE_END
		};

		string getRobotControlMessage();

		PFPerson &_person;
		int _state, _partNo;
};

#endif
