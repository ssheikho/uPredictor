#include "BoundingBox.h"

#include <opencv2\imgproc.hpp>

BoundingBox::BoundingBox() :
	_c1(pair<long, long>(0, 0))
	, _c2(pair<long, long>(0, 0))
	, _midPt(pair<long,long>(0, 0))
{}

BoundingBox::~BoundingBox() {}

void BoundingBox::updateBounds(pair<pair<long, long>, pair<long, long >> pts) {
	_c1 = pts.first;
	_c2 = pts.second;
	_midPt =
		pair<long, long>(
			(_c1.first + _c1.second) / 2
			, (_c2.first + _c2.second) / 2);
}

void BoundingBox::drawBB(cv::Mat &a, cv::Scalar &color, int thickness) {
	CvPoint ptA, ptB, ptC, ptD;
	ptA.x = _c1.first;
	ptA.y = _c1.second;
	ptB.x = _c2.first;
	ptB.y = _c1.second;
	ptC.x = _c2.first;
	ptC.y = _c2.second;
	ptD.x = _c1.first;
	ptD.y = _c2.second;

	cv::line(a, ptA, ptB, color, thickness, 8, 0);
	cv::line(a, ptB, ptC, color, thickness, 8, 0);
	cv::line(a, ptC, ptD, color, thickness, 8, 0);
	cv::line(a, ptD, ptA, color, thickness, 8, 0);
}