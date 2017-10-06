#ifndef SMC_MOVE_BACK_EVENT_H
#define SMC_MOVE_BACK_EVENT_H

#include "smceventmodel.h"

class SMCMoveBackEvent : public SMCEventModel {
	public:
		SMCMoveBackEvent(ParamList *pl, WorldModel *wm, SMCConnection &smcc,
			bool liveFire);
		~SMCMoveBackEvent();

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
