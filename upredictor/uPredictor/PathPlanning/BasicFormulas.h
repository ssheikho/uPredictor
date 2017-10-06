#ifndef BASIC_FORMULAS_H
#define BASIC_FORMULAS_H


/*
Eigen Block of size (p,q), starting at (i,j)	
matrix.block(i,j,p,q);
matrix.block<p,q>(i,j);
*/

using namespace Eigen;

template<typename T>
T simpleThirdOrder(T constTerm, T aConst, T bConst, T cConst, T parametricTerm) {
	return constTerm +
		parametricTerm * aConst +
		parametricTerm * parametricTerm * bConst +
		parametricTerm * parametricTerm * parametricTerm * cConst;
}

template<typename T>
Eigen::Matrix<T, Dynamic, Dynamic> linearInterp(
	Eigen::Matrix<T, Dynamic, 1> from
	, Matrix<T, Dynamic, 1> to
	, size_t nSlices) {
	Eigen::Matrix<T, Dynamic, Dynamic> along = to - from;
	T alongNorm = along.norm();
	Eigen::Matrix<T, Dynamic, Dynamic> alongN = along / alongNorm;
	T sliceSize = alongNorm / T(nSlices);
	Eigen::Matrix<T, Dynamic, Dynamic> slice = sliceSize * alongN;

	Eigen::Matrix<T, Dynamic, Dynamic> outPts(from.rows(), nSlices + 1);
	for(size_t i = 0; i <= nSlices; i++) {
		outPts.block(0, i, from.rows(), 1) = slice * T(i) + from; 
	}

	return outPts;
}


template<typename T>
Eigen::Matrix<T, Dynamic, Dynamic> EllipticalInterp(
	Eigen::Matrix<T, Dynamic, 1> from
	, Matrix<T, Dynamic, 1> to
	, size_t nSlices) {

	Eigen::Matrix<T, Dynamic, Dynamic> vect = to - from;
	T vectNorm = vect.norm();
	Eigen::Matrix<T, Dynamic, Dynamic> vectN = vect / vectNorm;
	T sliceSize = M_PI / T(nSlices);
	
	T a = vectNorm / T(2.0);
	T b = vectNorm / T(5.0);
	Eigen::Matrix<T, Dynamic, Dynamic> 
		thetaVect(1, nSlices + 1);
	
	for(size_t i = 0; i <= nSlices; i++)
		thetaVect(1, i); 		
		

	Matrix<double,Dynamic,Dynamic> pointOnEllipsePseudo2D(3,nSlices);
	for(size_t i = 0; i <= nSlices; i++) {
		pointOnEllipsePseudo2D(0,0) = a * cos(thetaVect(1, i));
		pointOnEllipsePseudo2D(1,0) = b * sin(thetaVect(1, i));
		pointOnEllipsePseudo2D(2,0) = 1.0;
	}
		
	Eigen::Matrix<T, Dynamic, Dynamic> slice = sliceSize * vectN;

	Eigen::Matrix<T, Dynamic, Dynamic> outPts(from.rows(), nSlices + 1);
	for(size_t i = 0; i <= nSlices; i++) {
		outPts.block(0, i, from.rows(), 1) = slice * T(i) + from; 
	}

	return outPts;
}



#endif
