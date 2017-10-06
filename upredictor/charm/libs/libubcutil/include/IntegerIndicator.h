#ifndef INTEGER_INDICATOR_H
#define INTEGER_INDICATOR_H

#include <vector>

using namespace std;

class IntegerIndicatorListener;

class IntegerIndicator {
public:
	void addIIListener(IntegerIndicatorListener *iil);

	virtual int intVal() = 0;

protected:
	void fireUpdate();

	vector<IntegerIndicatorListener *> _iil;
};

#endif