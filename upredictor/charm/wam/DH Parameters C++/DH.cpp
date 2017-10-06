#include <iostream>
#include <Eigen/Dense>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Eigen;
using namespace std;

class DH {
	private:
		Matrix4f A;
		float a; 
		float d;
		float alpha;
		float theta;
		void constructMatrix(void);

	public:
		Matrix4f getMatrix(void);
		void setTheta(float theta);
		DH(float a, float d, float alpha, float theta);


};

DH::DH(float a_1, float d_1, float alpha_1, float theta_1) {
	a = a_1;
	d = d_1;
	alpha = alpha_1;
	theta = theta_1;

	constructMatrix();
}

Matrix4f DH::getMatrix(void) {
	return A;
}

void DH::setTheta(float theta_1) {
	theta = theta_1;
	constructMatrix();
}

void DH::constructMatrix(void) {
	A(0, 0) = cos(theta); A(0, 1) = sin(theta)*cos(alpha); A(0, 2) = sin(theta)*sin(alpha); A(0, 3) = a*cos(theta);
	A(1, 0) = sin(theta); A(1, 1) = cos(theta)*cos(alpha); A(1, 2) = -cos(theta)*sin(alpha); A(1, 3) = a*sin(theta);
	A(2, 0) = 0; A(2, 1) = sin(alpha); A(2, 2) = cos(alpha); A(2, 3) = d;
	A(3, 0) = 0; A(3, 1) = 0; A(3, 2) = 0; A(3, 3) = 1;
}


int main() {
	DH test(0.0, 0.0, -M_PI_2, M_PI_4);

	cout << "test class";
	cout << test.getMatrix();

	test.setTheta(0);
	cout << test.getMatrix();

	std::cin.get();
	return 0;
}


