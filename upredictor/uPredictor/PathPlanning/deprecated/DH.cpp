#include "DH.h"

#include <iostream>

using namespace Eigen;
using namespace std;

DH::DH(double a, double alpha, double d, double theta) :
	_a(a)
	, _alpha(alpha)
	, _d(d)
	, _theta(theta) {
	computeDH();
}

DH::~DH() {}

void DH::setValues(double a, double alpha, double d, double theta) {
	_a = a;
	_alpha = alpha;
	_d = d;
	_theta = theta;
	computeDH();
}

void DH::setTheta(double theta) {
	_theta = theta;
	computeDH();
}

MatrixXd DH::getMat() {
	return _mat;
}

void DH::prettyPrint() {
	cout << "DH:	" << _a << "	" << _alpha << "	" << _d << "	" <<
		_theta << endl;
	cout << _mat << endl;
}

void DH::computeDH() {
	_mat = dhTransform(_a, _alpha, _d, _theta);
}

MatrixXd DH::dhTransform(double a, double alpha, double d, double theta) {
	MatrixXd retVals(4, 4);

	retVals(0,0) = cos(theta);
	retVals(0,1) = -cos(alpha) * sin(theta);
	retVals(0,2) = sin(alpha) * sin(theta);
	retVals(0,3) = a * cos(theta);


	retVals(1,0) = sin(theta);
	retVals(1,1) = cos(alpha) * cos(theta);
	retVals(1,2) = -cos(theta) * sin(alpha);
	retVals(1,3) = a * sin(theta);

	retVals(2,0) = 0.0;
	retVals(2,1) = sin(alpha);
	retVals(2,2) = cos(alpha);
	retVals(2,3) = d;

	retVals(3,0) = 0.0;
	retVals(3,1) = 0.0;
	retVals(3,2) = 0.0;
	retVals(3,3) = 1.0;

	return retVals;
}
