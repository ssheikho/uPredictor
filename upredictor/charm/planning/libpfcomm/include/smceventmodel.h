#ifndef SMC_EVENT_MODEL_H
#define SMC_EVENT_MODEL_H

#include "lamecomm.h"
#include "outmessageevent.h"
#include "smcmessagehandler.h"
#include "stopwatch.h"

#include <string>

using namespace std;

class ParamList;
class SMCConnection;
class WorldModel;

//GetPart SMCGetPartEvent
//MoveToPerson SMCMoveToPersonEvent
//StartHandover SMCStartHandoverEvent
//StartMoveBack SMCMoveBackEvent

class SMCEventModel : public SMCMessageHandler {
	public:
		SMCEventModel(ParamList *pl, WorldModel *wm, SMCConnection &smcc,
			bool liveFire);
		~SMCEventModel();

		void sendRobotControlMessage();
		void sendAck();

		virtual string getRobotControlMessage() = 0;
		virtual bool isDone() = 0;
		virtual void start() = 0;

	protected:
		class StartMessage : public OutMessageEvent {
			public:
				StartMessage(SMCEventModel *em);
				~StartMessage();

				void packMessage(char *payload);

			protected:
				SMCEventModel *_em;
		};

		class AckMessage : public OutMessageEvent {
			public:
				AckMessage();
				~AckMessage();

				void packMessage(char *payload);
		};

		ParamList *_pl;
		WorldModel *_wm;
		SMCConnection &_smcc;
		bool _liveFire;
		StartMessage _startMess;
		AckMessage _ackMess;
		
		StopWatch _sw;
};

#endif
