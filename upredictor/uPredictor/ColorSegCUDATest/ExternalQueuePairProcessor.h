#ifndef EXTERNAL_QUEUE_PAIR_PROCESSOR_H
#define EXTERNAL_QUEUE_PAIR_PROCESSOR_H

#include "TypeRecipient.h"

template<typename T> class ExternalQueuePairProcessor :
public TypeRecipient<ExternalQueuePair<T>> {
public:
	ExternalQueuePairProcessor() {}
	~ExternalQueuePairProcessor() {}

	void processType(ExternalQueuePair<T> t) {
		t.update();
	}

	void onStartup() {}
};

#endif