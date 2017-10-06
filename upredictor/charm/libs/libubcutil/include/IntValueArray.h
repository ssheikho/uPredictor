#ifndef INT_VALUE_ARRAY_H
#define INT_VALUE_ARRAY_H

#include <vector>

using namespace std;

class IntValueArrayListener;

class IntValueArray {
public:
	virtual ~IntValueArray();

	virtual void set(int index, int value, void *origin) = 0;
	virtual int get(int index) = 0;

	virtual bool hasMin(int index) = 0;
	virtual bool hasMax(int index) = 0;
	virtual int getMinVal(int index) = 0;
	virtual int getMaxVal(int index) = 0;

	virtual size_t getNVals() = 0;

	void addIVAListener(IntValueArrayListener *ival);
	void removeIVAListener(IntValueArrayListener *ival);

protected:
	void fireUpdate(int index, int value, void *origin);

	vector<IntValueArrayListener *> _ival;
};

#endif