#ifndef VALUE_LISTENER_H
#define VALUE_LISTENER_H

#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

template<typename T> class ValueListener :
	public TypeBroadcaster<T>
	, public TypeRecipient<T> {
public:
	ValueListener(T t) : _t(t) {}

	void processType(T t) {
		_t = t;
		TypeBroadcaster<T>::fireUpdate(_t);
	}

	void onStartup() {}

	T _t;
};

#endif
