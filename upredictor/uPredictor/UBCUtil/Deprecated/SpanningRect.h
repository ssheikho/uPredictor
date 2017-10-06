#ifndef SPANNING_RECT_H
#define SPANNING_RECT_H

#include "IndexedToggle.h"

#include <utility>

using namespace std;

class SpanningRect :
public IndexedToggle {

public:
	SpanningRect();
	~SpanningRect();

	void setSpanningPt(pair<int, int> p);

	//IndexedToggle
	void updateToggle(size_t index, bool val);

	pair<int, int> getPt(size_t index);
	size_t getNPts();

protected:
	bool _inUse, _curPt;
	pair<int, int> _ptA, _ptB;
};

#endif