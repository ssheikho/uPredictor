#ifndef ELLIPSE_IMPLICIT_FIT_H
#define ELLIPSE_IMPLICIT_FIT_H

#include "FitFunctions.h"
#include "Plane.h"
#include <UBCUtil.h>

#include <cmath>

#include <Eigen/Dense>

using namespace std;

template<typename T>
class EllipseImplicitFit {
public:
	EllipseImplicitFit(Matrix<T, Dynamic, Dynamic> inPtsAlongCols) :
		_inPtsAlongCols(inPtsAlongCols)
		, _plane(_inPtsAlongCols)
	{
		Vector3d zAxis(3,1);
		zAxis << 0.0, 0.0, 1.0;
		_dotProduct = _plane.getPlaneNormalVectN().dot(zAxis);
		_crossProduct = _plane.getPlaneNormalVectN().cross(zAxis);

		_rotToXY =
			AngleAxisd(atan2(_crossProduct.norm(), _dotProduct)
				, _crossProduct.normalized()).toRotationMatrix();
		_ptsXYAlongCols = _rotToXY * _inPtsAlongCols;
		_conicConstraintMat = buildConicConstraintMat(_ptsXYAlongCols);
		_conicVect = svdSolve(_conicConstraintMat);
		_conicImplicit = arrangeConicVectIntoImplicit(_conicVect);
	}

	~EllipseImplicitFit() {}

	Plane getPlane() {
		return _plane;
	}

	Matrix<T, Dynamic, Dynamic> getRotToXY() {
		return _rotToXY;
	}

	Matrix<T, Dynamic, Dynamic> getPtsXYAlongCols() {
		return _ptsXYAlongCols;
	}

	Matrix<T, Dynamic, Dynamic> getConicConstraintMat() {
		return _conicConstraintMat;
	}

	Matrix<T, Dynamic, Dynamic> getConicVect() {
		return _conicVect;
	}

	Matrix<T, Dynamic, Dynamic> getConicImplicit() {
		return _conicImplicit;
	}

protected:
	Matrix<T, Dynamic, Dynamic> _inPtsAlongCols;
	Plane _plane;
	double _dotProduct;
	Matrix<T,3,1> _crossProduct;
	Matrix<T, Dynamic, Dynamic> _rotToXY
			, _ptsXYAlongCols
			, _conicConstraintMat
			, _conicVect
			, _conicImplicit;
};

#endif
