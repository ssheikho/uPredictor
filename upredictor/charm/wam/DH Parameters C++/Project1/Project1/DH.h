#include <iostream>
#include <Eigen/Dense>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Eigen;
using namespace std;

class DH {
private:
	Matrix4d A;
	double a;
	double d;
	double alpha;
	double theta;
	void constructMatrix(void);

public:
	Matrix4d getMatrix(void);
	void setTheta(double theta);
	DH(double a, double d, double alpha, double theta);
};