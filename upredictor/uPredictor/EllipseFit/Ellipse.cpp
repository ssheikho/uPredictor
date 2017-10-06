#include "Ellipse.h"
MatrixXd Ellipse::getPointAtThetasH(Eigen::MatrixXd thetas) {
	size_t nTheta = thetas.cols();

	MatrixXd retVals(3, nTheta);

	for(size_t i = 0; i < nTheta; i++)
		retVals.block(0,i,3,1) = getPointAtThetaH(thetas(0,i));
	
	return retVals;
}
