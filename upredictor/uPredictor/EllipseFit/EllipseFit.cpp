#include "Ellipse3D.h"
#include "ParseMathematica.h"
#include <UBCUtil.h>

/*
#include "FitFunctions.h"
#include "LinearAlgebra.h"
#include "RigidTrans2D.h"
*/

#include <Eigen/Dense>
//#include <Eigen/SVD>

//#include <cmath>
#include <iostream>

using namespace Eigen;
using namespace std;

MatrixXd fixThetas(MatrixXd a) {
	MatrixXd retVal(a.rows(), a.cols());

	double curTheta = a(0,0);
	while(curTheta >= -M_PI) curTheta -= M_PI;
	while(curTheta <= M_PI) curTheta += M_PI;
	retVal(0,0) = curTheta;

	for(size_t i = 1; i < a.cols(); i++) {
		double curTheta = a(0,i);
		while(curTheta >= -M_PI) curTheta -= 2.0 * M_PI;
		while(curTheta <= M_PI) curTheta += 2.0 * M_PI;

		double testA = curTheta + 2.0 * M_PI;
		double testB = curTheta - 2.0 * M_PI;
		
		double distNull = curTheta - retVal(0, i - 1);
		double distA = testA - retVal(0, i - 1);
		double distB = testB - retVal(0, i - 1);

		retVal(0, i) = distNull < distA ? curTheta : testA;
		retVal(0, i) = distNull < distB ? curTheta : testB;
	}

	return retVal;
}

MatrixXd simpleGradientAcrossCols(MatrixXd a) {
	MatrixXd retVal(a.rows(), a.cols() - 1);

	for(size_t i = 1; i < a.cols(); i++) {
		for(size_t j = 0; j < a.rows(); j++) {
			retVal(j, i - 1) = a(j, i) - a(j, i - 1);
		}
	}

	return retVal;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	MatrixXd inPtsAlongRows = parseMathematica(getWholeFile(argv[1]));

	MatrixXd inPtsAlongCols = inPtsAlongRows.transpose();
	cout << inPtsAlongRows <<endl;
/*
	Ellipse3D<double> e3D(inPtsAlongCols);
	MatrixXd thetas = e3D.findThetas();
	MatrixXd pts = e3D.getEllipse().getPointAtThetasH(thetas);
	

	MatrixXd fixedThetas = fixThetas(thetas);
	MatrixXd speed = simpleGradientAcrossCols(fixedThetas);
	MatrixXd acceleration = simpleGradientAcrossCols(speed);
	MatrixXd jerk = simpleGradientAcrossCols(acceleration);

	printEigenMathematica(e3D.getEIF().getPtsXYAlongCols(), cout, "inPts");
	printEigenMathematica(pts, cout, "outPts");
	printEigenMathematica(fixedThetas, cout, "fixedThetas");
	printEigenMathematica(speed, cout, "speed");
	printEigenMathematica(acceleration, cout, "acceleration");
	printEigenMathematica(jerk, cout, "jerk");
*/
	return 0;
}
