#include "RegisteredBB.h"

#ifdef _WIN32
#include <opencv2/imgproc.hpp>
#elif __linux__
#include <opencv2/imgproc/imgproc.hpp>
#endif

RegisteredBB::RegisteredBB() :
	_minX2D(0.0), _maxX2D(0.0),
	_minY2D(0.0), _maxY2D(0.0),
	_cX2D(0.0), _cY2D(0.0), _cX3D(0.0), _cY3D(0.0), _cZ3D(0.0)
{}

RegisteredBB::~RegisteredBB() {}

void RegisteredBB::updateBounds(
	double minX2D, double maxX2D,
	double minY2D, double maxY2D,
	double minX3D, double maxX3D,
	double minY3D, double maxY3D,
	double minZ3D, double maxZ3D
	) {
	_minX2D = minX2D; _maxX2D = maxX2D;
	_minY2D = minY2D; _maxY2D = maxY2D;

	_minX3D = minX3D; _maxX3D = maxX3D;
	_minY3D = minY3D; _maxY3D = maxY3D;
	_minZ3D = minZ3D; _maxZ3D = maxZ3D;

	_cX2D = (_minX2D + _maxX2D) / 2.0;
	_cY2D = (_minY2D + _maxY2D) / 2.0;

	_cX3D = (_minX3D + _maxX3D) / 2.0;
	_cY3D = (_minY3D + _maxY3D) / 2.0;
	_cZ3D = (_minZ3D + _maxZ3D) / 2.0;
}

void RegisteredBB::drawBB(cv::Mat &a, cv::Scalar &color, int thickness) {
	CvPoint ptA, ptB, ptC, ptD;
	ptA.x = _minX2D;
	ptA.y = _minY2D;
	ptB.x = _maxX2D;
	ptB.y = _minY2D;
	ptC.x = _maxX2D;
	ptC.y = _maxY2D;
	ptD.x = _minX2D;
	ptD.y = _maxY2D;

	cv::line(a, ptA, ptB, color, thickness, 8, 0);
	cv::line(a, ptB, ptC, color, thickness, 8, 0);
	cv::line(a, ptC, ptD, color, thickness, 8, 0);
	cv::line(a, ptD, ptA, color, thickness, 8, 0);
}
