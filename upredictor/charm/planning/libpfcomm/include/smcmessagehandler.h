#ifndef SMC_MESSAGE_HANDLER_H
#define SMC_MESSAGE_HANDLER_H

#include "SMC/Client.h"
#include "SMCClient.h"
#include "SMC/SMCProtocol.h"

using namespace SMC;

class SMCMessageHandler {
	public:
		SMCMessageHandler();
		~SMCMessageHandler();
	
		virtual void process(const CProtocol::tSMCPayload *payload) = 0;
};

#endif
