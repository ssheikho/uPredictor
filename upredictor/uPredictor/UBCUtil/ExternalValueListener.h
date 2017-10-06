#ifndef EXTERNAL_VALUE_LISTENER_H
#define EXTERNAL_VALUE_LISTENER_H

#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

template<typename T> class ExternalValueListener :
	public TypeBroadcaster<T>
	, public TypeRecipient<T> {
public:
	ExternalValueListener(T *t) : _t(t) {}

	void processType(T t) {
		*_t = t;
		this->fireUpdate(*_t);
	}

	void onStartup() {}

	T *_t;
};

#endif
