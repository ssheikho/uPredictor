#ifndef PROCESS_MULTIPLEXER_H
#define PROCESS_MULTIPLEXER_H

#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <vector>

using namespace std;

template<typename T> class ProcessMultiplexer :
public TypeRecipient<T>
, public TypeBroadcaster<T> {

public:
	void processType(T t) {
		fireUpdate(t);
	}

	void onStartup() {}
};

#endif