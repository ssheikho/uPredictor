#include "RigidTransformation.h"

#include <Eigen/Geometry>

RigidTransformation::RigidTransformation() : _rt(Matrix4d::Zero()) {
	_rt(3,3) = 1.0;
}

RigidTransformation::~RigidTransformation() {}

void RigidTransformation::update(
	double rX, double rY, double rZ
	, double tX, double tY, double tZ) {
	Vector3d r(rX, rY, rZ);

	double theta = r.norm();
	r /= theta;
	AngleAxisd aa(theta, r);
	_rt.block<3,3>(0,0) = aa.toRotationMatrix();

	_rt(0,3) = tX;
	_rt(1,3) = tY;
	_rt(2,3) = tZ;
}

MatrixXd RigidTransformation::getMat() {
	return _rt;
}
