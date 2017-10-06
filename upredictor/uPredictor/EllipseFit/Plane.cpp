#include "Plane.h"
#include <UBCUtil.h>

Plane::Plane(MatrixXd inPts) :
	_plane(svdSolve(cartToHom(inPts).transpose()))
	, _planeNormalVect(_plane.block(0,0,3,1))
	, _norm(_planeNormalVect.norm())
	, _planeN(_plane / _norm)
	, _planeNormalVectN(_planeN.block(0,0,3,1)) {}

Plane::~Plane() {}

Vector4d Plane::getPlane() {
	return _plane;
}

Vector3d Plane::getPlaneNormalVect() {
	return _planeNormalVect;
}

double Plane::getNorm() {
	return _norm;
}

Vector4d Plane::getPlaneN() {
	return _planeN;
}

Vector3d Plane::getPlaneNormalVectN() {
	return _planeNormalVectN;
}
