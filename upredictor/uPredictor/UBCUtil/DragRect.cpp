#include "DragRect.h"

DragRect::DragRect() :
	_a(pair<int,int>(0,0))
	, _b(pair<int, int>(0, 0))
	, _min(pair<int, int>(0, 0))
	,_max(pair<int, int>(0, 0))
	{}

DragRect::DragRect(pair<int, int> a, pair<int, int>b) :
	_a(a)
	, _b(b)
{
	computeMinMax();
}

DragRect::~DragRect() {}

void DragRect::invertXBy(int xOffset) {
	_a.first = xOffset - _a.first;
	_b.first = xOffset - _b.first;
	computeMinMax();
}

void DragRect::computeMinMax() {
	_min = pair<int, int>(
		_a.first <= _b.first ? _a.first : _b.first
		, _a.second <= _b.second ? _a.second : _b.second);
	_max = pair<int, int>(
		_a.first >= _b.first ? _a.first : _b.first
		, _a.second >= _b.second ? _a.second : _b.second);
}