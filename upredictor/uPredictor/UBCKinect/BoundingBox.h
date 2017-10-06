#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Allocator.h"
#include "ArrayPt3DCollection.h"
#include "SimplePool.h"

#include <opencv\cv.h>

#include <utility>

using namespace std;

class BoundingBox {
public:
	BoundingBox();
	~BoundingBox();

	void updateBounds(pair<pair<long, long>, pair<long, long >> pts);

	void drawBB(cv::Mat &a, cv::Scalar &color, int thickness);

	pair<long, long> _c1, _c2, _midPt;
};

#endif