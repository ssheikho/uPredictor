#ifndef VALUE_ARRAY_H
#define VALUE_ARRAY_H

#include "TypeBroadcaster.h"

template<typename T> class ValueArray :

//Reporting changes to values
public TypeBroadcaster< pair<long,T> >	

//Reporting changes to the value array
, public TypeBroadcaster<ValueArray<T> *>	

{

protected:
	virtual void setProt(long index, T value) = 0;

public:
	virtual size_t getNVals() = 0;

	void set(long index, T value) {
		setProt(index, value);
		TypeBroadcaster< pair<long, T> >::fireUpdate(
			pair<long, T>(index, value));
	}

	virtual T get(long index) = 0;

	virtual bool hasMin(long index) = 0;
	virtual bool hasMax(long index) = 0;

	virtual T getMinVal(long index) = 0;
	virtual T getMaxVal(long index) = 0;
};

#endif
