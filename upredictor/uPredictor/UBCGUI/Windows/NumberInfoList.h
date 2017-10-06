#ifndef NUMBER_INFO_LIST_H
#define NUMBER_INFO_LIST_H

#include "GridLayout.h"
#include "TypeBroadcaster.h"

#include <vector>

using namespace std;

class UBCEntry;

class NumberInfoList {
public:
	NumberInfoList(
		LayoutContainer *parent
		, int labelW
		, int dataW
		, int rowH = 25);
	~NumberInfoList();

	void addLongLabel(wstring label, TypeBroadcaster<long> *tb);
	void addDoubleLabel(wstring label, TypeBroadcaster<double> *tb);

protected:
	int _labelW, _dataW, _rowH;
	GridLayout _gl;
	vector<UBCEntry *> _l, _d;
};

#endif