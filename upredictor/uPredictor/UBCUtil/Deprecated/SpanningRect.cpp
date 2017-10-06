#include "SpanningRect.h"

SpanningRect::SpanningRect() : _inUse(false), _curPt(false) {}
SpanningRect::~SpanningRect() {}

void SpanningRect::setSpanningPt(pair<int, int> p) {
	if (_curPt) _ptA = p;
	else _ptB = p;
	_curPt = !_curPt;
}

void SpanningRect::updateToggle(size_t index, bool val) {
	switch (index) {
	case 0:
		_inUse = val;
		break;
	}
}

pair<int, int> SpanningRect::getPt(size_t index) {
	pair<int, int> retVal;
	switch (index) {
	case 0:
		retVal = _ptA;
		break;
	case 1:
		retVal = _ptB;
		break;
	}
	return retVal;
}

size_t SpanningRect::getNPts() {
	return 2;
}