#include "LinearAlgebra.h"

#include <iostream>

using namespace Eigen;
using namespace std;

std::pair<Eigen::MatrixXd, Eigen::MatrixXd>
	solveEigensystem(Eigen::MatrixXd a) {
	EigenSolver<MatrixXd> eigensolver(a);

	//cout << eigensolver.eigenvalues() << endl;
	//cout << eigensolver.eigenvectors() << endl;

	//SelfAdjointEigenSolver<MatrixXd> eigensolver(a);

	std::map<double, MatrixXd> retVal;

	for(size_t i = 0; i < a.rows(); i++)
		retVal.insert(
			pair<double, MatrixXd>(
				eigensolver.eigenvalues()(i).real()
				, eigensolver.eigenvectors().real().block(0, i, a.rows(), 1)));

	MatrixXd eigenValues(a.rows(), 1);
	MatrixXd eigenVectors(a.rows(), a.rows());
	size_t i = 0;
	for(std::map<double, Eigen::MatrixXd>::reverse_iterator iter =
			retVal.rbegin();
		iter != retVal.rend(); iter++) {
		eigenValues(i,0) = iter->first;
		eigenVectors.block(0,i,a.rows(),1) = iter->second;
		i++;
	}

	return std::pair<MatrixXd, MatrixXd>(eigenValues, eigenVectors);
}
