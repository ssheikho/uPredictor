#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "EllipseImplicitFit.h"
#include "FitFunctions.h"
#include "LinearAlgebra.h"

#include <cmath>

#include "RigidTrans2D.h"

using namespace Eigen;

//template<typename T>
class Ellipse {
public:
	Ellipse(double a, double b, double alpha, double cX, double cY) :
		_a(a), _b(b), _rt2D(alpha, cX, cY) {}

	Ellipse() : _rt2D(0.0, 0.0, 0.0) {}
	Ellipse(EllipseImplicitFit<double> eif) : _rt2D(0.0, 0.0, 0.0) {
		MatrixXd a33 = aThirtyThreeFromConicSolution(eif.getConicVect());
		std::pair<MatrixXd, MatrixXd> solution = solveEigensystem(a33);
		double detImp = eif.getConicImplicit().determinant();
		double detA33 = a33.determinant();
		double k = -detImp / detA33;

		_a = sqrt(k / solution.first(0,0));
		_b = sqrt(k / solution.first(1,0));

		double ccBottomTerm = 4.0 *
			eif.getConicVect()(0,0) * eif.getConicVect()(2,0)
			- eif.getConicVect()(1,0) * eif.getConicVect()(1,0);
		double ccXTerm = (eif.getConicVect()(1,0) * eif.getConicVect()(4,0)
			- 2.0 * eif.getConicVect()(2,0) * eif.getConicVect()(3,0)) /
			ccBottomTerm;
		double ccYTerm = (eif.getConicVect()(3,0) * eif.getConicVect()(1,0)
			- 2.0 * eif.getConicVect()(0,0) * eif.getConicVect()(4,0)) /
			ccBottomTerm;
		double alphaAngle = atan2(solution.second(1,0), solution.second(0,0));

		_rt2D.setRT(alphaAngle, ccXTerm, ccYTerm);
	}

	~Ellipse() {}
	
	void setAB(double a, double b) {
		_a = a;
		_b = b;
	}

	double getA() {
		return _a;
	}

	double getB() {
		return _b;
	}

	RigidTrans2D getRT2D() {
		return _rt2D;
	}

	Matrix<double,Dynamic,Dynamic> getPointAtThetaH(double theta) {
		Matrix<double,Dynamic,Dynamic> pointOnEllipsePseudo2D(3,1);
		pointOnEllipsePseudo2D(0,0) = _a * cos(theta);
		pointOnEllipsePseudo2D(1,0) = _b * sin(theta);
		pointOnEllipsePseudo2D(2,0) = 1.0;

		return _rt2D.getRT() * pointOnEllipsePseudo2D;
	}

	double getPointXAtThetaH(double theta) {
		return getPointAtThetaH(theta)(0,0);
	}

	double getPointYAtThetaH(double theta) {
		return getPointAtThetaH(theta)(1,0);
	}

	double getPointWAtThetaH(double theta) {
		return getPointAtThetaH(theta)(2,0);
	}


	Matrix<double,Dynamic,Dynamic> getPointAtThetasH(
			Matrix<double, Dynamic, Dynamic> thetas) {
		size_t nTheta = thetas.cols();

		Matrix<double,Dynamic,Dynamic> retVals(3, nTheta);

		for(size_t i = 0; i < nTheta; i++)
			retVals.block(0,i,3,1) = getPointAtThetaH(thetas(0,i));
	
		return retVals;
	}

protected:
	double _a, _b;
	RigidTrans2D _rt2D;
};

#endif
