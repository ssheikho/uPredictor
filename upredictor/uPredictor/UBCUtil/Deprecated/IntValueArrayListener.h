#ifndef INT_VALUE_ARRAY_LISTENER_H
#define INT_VALUE_ARRAY_LISTENER_H

#include <memory>

using namespace std;

class IntValueArray;

class IntValueArrayListener {
public:
	virtual void updateIVAL(IntValueArray *iva, int index, int value, void *origin) = 0;
};

#endif