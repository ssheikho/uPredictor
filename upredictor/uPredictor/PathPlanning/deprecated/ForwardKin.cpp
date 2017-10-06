#include "ForwardKin.h"

//#include <Eigen/Dense>
#include <Eigen/SVD>

//#include <cmath>
#include <iostream>

using namespace Eigen;
using namespace std;

ForwardKin::ForwardKin(size_t nJoints) : _nJoints(nJoints)
	, _joint(new DH[_nJoints]) {
	//_joint[0]
	//setDHParameters();
}

ForwardKin::~ForwardKin() {
	delete[] _joint;
}

void ForwardKin::setThetaVect(MatrixXd thetaVect) {
	for(size_t i = 0; i < _nJoints; i++)
		_joint[i].setTheta(thetaVect(i,0));
}

void ForwardKin::setDHParameters(MatrixXd a, MatrixXd alpha, MatrixXd d){
	for(size_t i = 0; i < _nJoints; i++)
		_joint[i].setValues(a(i,0), alpha(i,0), d(i,0), 0.0);
}

ForwardKin ForwardKin::generateBarrettWAM() {
	ForwardKin retVal(7);

	MatrixXd a(7,1);
	MatrixXd alpha(7,1);
	MatrixXd d(7,1);
	
	a << 0.0, 0.0, 0.045, -0.045, 0.0, 0.0, 0.0;
	alpha << -M_PI/2.0, M_PI/2.0, -M_PI/2.0, M_PI/2.0, -M_PI/2.0, M_PI/2.0, 0.0;
	d << 0.0, 0.0, 0.55, 0.0, 0.3 ,0.0, 0.06;

	retVal.setDHParameters(a, alpha, d);

	return retVal;
}

MatrixXd ForwardKin::getMat(size_t toDOF) {
	MatrixXd retVal = MatrixXd::Identity(4,4);

	for(size_t i = 0; (i < _nJoints) && (i < toDOF); i++)
		retVal = retVal * _joint[i].getMat();
	
	return retVal;
}

DH &ForwardKin::getDH(size_t index) {
	return _joint[index];
}

size_t ForwardKin::getNJoints() {
	return _nJoints;
}












