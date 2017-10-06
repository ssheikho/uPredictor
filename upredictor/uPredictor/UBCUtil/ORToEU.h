#ifndef OR_TO_EU_H
#define OR_TO_EU_H

#include "ExternalUpdateCollection.h"
//#include "ObjectBroadcaster.h"
#include "TypeBroadcaster.h"

template <typename T> class ORToEU :
	public TypeBroadcaster<T>::TypeRecipient
, public ExternalUpdateCollection {
public:
	ORToEU() {} 
	~ORToEU() {}

	void processType(T inObj) {
		update();
	}

};

#endif