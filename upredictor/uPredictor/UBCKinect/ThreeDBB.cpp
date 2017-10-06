#include "ThreeDBB.h"

#include <cmath>

ThreeDBB::ThreeDBB() :
	_minX3DBound(-10000.0), _maxX3DBound(10000.0)
	, _minY3DBound(-10000.0), _maxY3DBound(10000.0)
	, _minZ3DBound(-10000.0), _maxZ3DBound(10000.0)
	, _minX3D(0.0), _maxX3D(0.0)
	, _minY3D(0.0), _maxY3D(0.0)
	, _minZ3D(0.0), _maxZ3D(0.0) {}

ThreeDBB::ThreeDBB(int *segments, CameraSpacePoint *pts, size_t nPts, int seg) {
	update(segments, pts, nPts, seg);
}

void ThreeDBB::update(int *segments, CameraSpacePoint *pts, size_t nPts, int seg) {
	bool foundFirst = false;
	for (size_t i = 0; i < nPts; i++) {
		if(
			(segments[i] == seg) &&
				(	(std::isfinite(pts[i].X)) &&
					(std::isfinite(pts[i].Y)) &&
					(std::isfinite(pts[i].Z))
				)
			
			/*
				&&

				(	(pts[i].X > _minX3DBound) &&
					(pts[i].Y > _minY3DBound) &&
					(pts[i].Z > _minZ3DBound)
				) &&

				(	(pts[i].X < _maxX3DBound) &&
					(pts[i].Y < _maxY3DBound) &&
					(pts[i].Z < _maxZ3DBound)
				)
			*/
			)
		{
			if (foundFirst) {
				if (pts[i].X > _maxX3D) {
					_maxX3D = pts[i].X;
				}
				else if (pts[i].X < _minX3D) {
					_minX3D = pts[i].X;
				}

				if (pts[i].Y > _maxY3D) {
					_maxY3D = pts[i].Y;
				}
				else if (pts[i].Y < _minY3D) {
					_minY3D = pts[i].Y;
				}

				if (pts[i].Z > _maxZ3D) {
					_maxZ3D = pts[i].Z;
				}
				else if (pts[i].Z < _minZ3D) {
					_minZ3D = pts[i].Z;
				}
			} else {
				foundFirst = true;
				_maxX3D = _minX3D = pts[i].X;
				_maxY3D = _minY3D = pts[i].Y;
				_maxZ3D = _minZ3D = pts[i].Z;
			}
		}
	}
}

ThreeDBB::~ThreeDBB() {}