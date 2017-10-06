#include <iostream>
#include <Eigen/Dense>
#define _USE_MATH_DEFINES
#include <math.h>
#include "DH.h"

using namespace Eigen;
using namespace std;

DH::DH(double a_1, double d_1, double alpha_1, double theta_1) {
	a = a_1;
	d = d_1;
	alpha = alpha_1;
	theta = theta_1;

	constructMatrix();	
}

Matrix4d DH::getMatrix(void) {
	return A;
}

void DH::setTheta(double theta_1) {
	theta = theta_1;
	constructMatrix();
}

void DH::constructMatrix(void) {
	/*A(0, 0) = cos(theta); A(0, 1) = sin(theta)*cos(alpha); A(0, 2) = sin(theta)*sin(alpha); A(0, 3) = a*cos(theta);
	A(1, 0) = sin(theta); A(1, 1) = cos(theta)*cos(alpha); A(1, 2) = -cos(theta)*sin(alpha); A(1, 3) = a*sin(theta);
	A(2, 0) = 0; A(2, 1) = sin(alpha); A(2, 2) = cos(alpha); A(2, 3) = d;
	A(3, 0) = 0; A(3, 1) = 0; A(3, 2) = 0; A(3, 3) = 1;*/

	A << cos(theta), sin(theta)*cos(alpha), sin(theta)*sin(alpha), a*cos(theta),
		 sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), a*sin(theta),
		 0, sin(alpha), cos(alpha), d,
		 0, 0, 0, 1;	
}




