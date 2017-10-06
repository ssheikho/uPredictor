#ifndef TYPE_RECIPIENT_BROADCASTER_H
#define TYPE_RECIPIENT_BROADCASTER_H

#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

template<typename T> class TypeRecipientBroadcaster : 
	public TypeRecipient<T>
	, public TypeBroadcaster<T> {
public:
	virtual void processType(T t) = 0;
	virtual void addProc(shared_ptr<TypeRecipient<T>> proc) = 0;
};

#endif
