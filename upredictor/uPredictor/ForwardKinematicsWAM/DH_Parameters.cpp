#include <iostream>
#include <Eigen/Dense>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace Eigen;
using namespace std;

//Matrix4f DH(float theta, float alpha, float a, float d) {
//
//	Matrix4f A(4, 4);
//	
//	A(0, 0) = cos(theta); A(0, 1) = sin(theta)*cos(alpha); A(0, 2) = sin(theta)*sin(alpha); A(0, 3) = a*cos(theta);
//	A(1, 0) = sin(theta); A(1, 1) = cos(theta)*cos(alpha); A(1, 2) = -cos(theta)*sin(alpha); A(1, 3) = a*sin(theta);
//	A(2, 0) = 0; A(2, 1) = sin(alpha); A(2, 2) = cos(alpha); A(2, 3) = d;
//	A(3, 0) = 0; A(3, 1) = 0; A(3, 2) = 0; A(3, 3) = 1;
//
//	return A;
//
//}

//int main()
//{
//	VectorXf a(7), d(7), alpha(7);
//	a << 0, 0, 0.045, - 0.045, 0, 0, 0;
//	d << 0, 0, 0.55, 0, 0.3, 0, 0.060;
//	alpha << -M_PI_2, M_PI_2, -M_PI_2, M_PI_2, -M_PI_2, M_PI_2, 0;
//	MatrixXf A;
//	float theta = M_PI_4;
//
//	A = DH(theta, alpha(1), a(1), d(1));
//
//
//	//MatrixXd m = MatrixXd::Random(3, 3);
//	//m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
//	/*cout << "m =" << endl << m << endl;
//	VectorXd v(3);
//	v << 1, 2, 3;*/
//	cout << "A1 =" << A;
//	std::cin.get();
//}