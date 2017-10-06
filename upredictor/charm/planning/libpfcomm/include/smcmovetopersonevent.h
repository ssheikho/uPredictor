#ifndef SMC_MOVE_TO_PERSON_EVENT_H
#define SMC_MOVE_TO_PERSON_EVENT_H

#include "smceventmodel.h"

class SMCMoveToPersonEvent : public SMCEventModel {
	public:
		SMCMoveToPersonEvent(ParamList *pl, WorldModel *wm, SMCConnection &smcc,
			bool liveFire);
		~SMCMoveToPersonEvent();

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

		int _state;
};

#endif
