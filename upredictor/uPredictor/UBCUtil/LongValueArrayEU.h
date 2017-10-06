#ifndef LONG_VALUE_ARRAY_LOOP_H
#define LONG_VALUE_ARRAY_LOOP_H

#include "ExternalUpdate.h"
#include "ValueArray.h"

class LongValueArrayEU :
public ExternalUpdate {
public:
	LongValueArrayEU(
		ValueArray<long> *va
		, long index
		, bool loop
		);
	~LongValueArrayEU();

	//ExternalUpdate
	void update();
	bool hasFutureUpdates();

protected:
	ValueArray<long> *_va;
	long _index, _curVal;
	bool _loop;
};

#endif
