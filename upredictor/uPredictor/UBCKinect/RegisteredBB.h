#ifndef REGISTERED_BB_H
#define REGISTERED_BB_H

#include "Allocator.h"
#include "ArrayPt3DCollection.h"
#include "SimplePool.h"
#include "ThreeDBB.h"

#include <opencv/cv.h>

#include <utility>

using namespace std;

class RegisteredBB : public ThreeDBB {
public:
	RegisteredBB();
	~RegisteredBB();

	void updateBounds(
		double minX2D, double maxX2D,
		double minY2D, double maxY2D,
		double minX3D, double maxX3D,
		double minY3D, double maxY3D,
		double minZ3D, double maxZ3D
		);

	void drawBB(cv::Mat &a, cv::Scalar &color, int thickness);

	double
		_minX2D, _maxX2D, _minY2D, _maxY2D,
		_cX2D, _cY2D, _cX3D, _cY3D, _cZ3D;
};

#endif
