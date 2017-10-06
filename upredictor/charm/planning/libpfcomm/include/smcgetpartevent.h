#ifndef SMC_GET_PART_EVENT_H
#define SMC_GET_PART_EVENT_H

#include "smceventmodel.h"

class SMCGetPartEvent : public SMCEventModel {
	public:
		SMCGetPartEvent(ParamList *pl, WorldModel *wm, SMCConnection &smcc,
			bool liveFire);
		~SMCGetPartEvent();

		void process(const CProtocol::tSMCPayload *payload);
		bool isDone();
		void start();


	protected:
		string getRobotControlMessage();

		enum {
			STATE_NULL,
			STATE_START,
			STATE_INTERMEDIATE,
			STATE_END
		};

		int _state;
};

#endif
