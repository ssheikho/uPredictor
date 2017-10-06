#ifndef OUT_MESSAGE_EVENT_H
#define OUT_MESSAGE_EVENT_H

#include "SMC/Client.h"

using namespace SMC;

class OutMessageEvent {
	public:
		OutMessageEvent();
		~OutMessageEvent();

		virtual void packMessage(char *payload) = 0;
};

#endif

