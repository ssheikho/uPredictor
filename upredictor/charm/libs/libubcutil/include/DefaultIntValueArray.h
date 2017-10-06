#ifndef DEFAULT_INT_VALUE_ARRAY_H
#define DEFAULT_INT_VALUE_ARRAY_H

#include "IntValueArray.h"

#include <vector>

using namespace std;

class DefaultIntValueArray : public IntValueArray {
public:
	DefaultIntValueArray();
	~DefaultIntValueArray();

	void set(int index, int value, void *origin);
	int get(int index);

	bool hasMin(int index);
	bool hasMax(int index);
	int getMinVal(int index);
	int getMaxVal(int index);

	size_t getNVals();

	void addValue(bool hasMin, bool hasMax, int min, int max, int val);

protected:
	vector<bool> _hasMin, _hasMax;
	vector<int> _min, _max, _val;
};

#endif