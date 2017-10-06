#ifndef DRAG_RECT_H
#define DRAG_RECT_H

#include <utility>

using namespace std;

class DragRect {
public:
	DragRect();
	DragRect(pair<int, int> a, pair<int, int>b);
	~DragRect();

	void invertXBy(int xOffset);
	void computeMinMax();

	pair<int, int> _a, _b, _min, _max;
};

#endif