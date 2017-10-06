#ifndef INT_VALUE_ARRAY_MULTIPLEXER_H
#define INT_VALUE_ARRAY_MULTIPLEXER_H

#include "IntValueArray.h"
#include "IntValueArrayListener.h"

#include <vector>

using namespace std;

class IntValueArrayMultiplexer :
		public IntValueArray
	,	public IntValueArrayListener {
public:
	IntValueArrayMultiplexer();
	~IntValueArrayMultiplexer();

	void set(int index, int value, void *origin);
	int get(int index);

	bool hasMin(int index);
	bool hasMax(int index);
	int getMinVal(int index);
	int getMaxVal(int index);

	size_t getNVals();

	void addIVA(IntValueArray *iva, bool deleteOnDestructor, bool getFromThis);

	void updateIVAL(IntValueArray *iva, int index, int value, void *origin);

protected:
	vector<IntValueArray *> _iva;
	vector<bool> _deleteOnDestructor;
	vector<bool> _getFromThis;
};

#endif