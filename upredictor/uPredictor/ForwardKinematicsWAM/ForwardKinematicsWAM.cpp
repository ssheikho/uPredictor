#include <iostream>
#include <Eigen/Dense>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ForwardKinematicsWAM.h"


using namespace Eigen;
using namespace std;

ForwardKinematics::ForwardKinematics(VectorXd a_1, VectorXd d_1, VectorXd alpha_1, VectorXd theta_1) {
	a = a_1;
	d = d_1;
	alpha = alpha_1;
	theta = theta_1;

	constructAll();
}

void ForwardKinematics::setTheta(VectorXd theta_1) {
	theta = theta_1;
	int i = 0;
	for (DH currDH : matrixList) {
		currDH.setTheta(theta(i));
		i++;
	}
}


void ForwardKinematics::constructAll() {
	int i = 0;
	matrixList.clear();
	for (i = 0; i < 7; i++) {
		DH currDH(a(i), d(i), alpha(i), theta(i));  // it's saving the transpose matrix, why?
		//currDH = currDH.getMatrix();
		/*currDH = currDH.getMatrix().transpose();*/
		matrixList.push_back(currDH);
	}
}

Matrix4d ForwardKinematics::getDH7(void) {
	Matrix4d DH7 = matrixList.front().getMatrix();
	int i = 1;
	for (DH currDH : matrixList) {
		if (i == 1) { i = 2; continue; }
		DH7 = DH7*currDH.getMatrix();
	}
	
return DH7;
}

Matrix4d ForwardKinematics::getDH4(void) {
	Matrix4d DH4 = matrixList.front().getMatrix();
	int i = 0;
	for (DH currDH : matrixList) {
		if (i == 0) { i++; continue; }
		if (i > 3) { break; }
		DH4 = DH4*currDH.getMatrix();
		i++;
	}

	return DH4;
}

Matrix4d ForwardKinematics::getA1(void) {
	Matrix4d A1 = matrixList.front().getMatrix();
	return A1;
}


int main() {
	VectorXd a(7), d(7), alpha(7), theta(7);
		a << 0, 0, 0.045, -0.045, 0, 0, 0;
		d << 0, 0, 0.55, 0, 0.3, 0, 0.060;
		alpha << -M_PI_2, M_PI_2, -M_PI_2, M_PI_2, -M_PI_2, M_PI_2, 0;
		theta << M_PI_2, M_PI_2, M_PI_2, M_PI_2, M_PI_2, M_PI_2, M_PI_2;

		ForwardKinematics test(a, d, alpha, theta);

	cout << "\n test class A1 \n";
	cout << test.getA1();
	cout << "\n test class DH4 \n";
	cout << test.getDH4();
	cout << "\n test class DH7 \n ";
	cout << test.getDH7();

	//test.setTheta(0);
	//cout << test.getDH7();

	std::cin.get();
	return 0;
}
