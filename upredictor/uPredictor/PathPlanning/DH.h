#ifndef DH_H
#define DH_H

#include <Eigen/Core>

#include <iostream>

template<typename T>
class DH {
public:
	DH(T a = T(0.0), T alpha = T(0.0), T d = T(0.0), T theta = T(0.0)) :
		_a(a)
		, _alpha(alpha)
		, _d(d)
		, _theta(theta) {
		computeDH();
	}

	~DH() {}

	void setValues(T a, T alpha, T d, T theta) {
		_a = a;
		_alpha = alpha;
		_d = d;
		_theta = theta;
		computeDH();
	}

	void setTheta(T theta) {
		_theta = theta;
		computeDH();
	}

	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> getMat() {
		return _mat;
	}

	void prettyPrint() {
		std::cout << "DH:	" << _a << "	" << _alpha << "	" << _d <<
			"	" <<
			_theta << std::endl;
		std::cout << _mat << std::endl;
	}

	static Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> dhTransform(
		T a, T alpha, T d, T theta) {
		Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> retVals(4, 4);

		retVals(0,0) = cos(theta);
		retVals(0,1) = -cos(alpha) * sin(theta);
		retVals(0,2) = sin(alpha) * sin(theta);
		retVals(0,3) = a * cos(theta);


		retVals(1,0) = sin(theta);
		retVals(1,1) = cos(alpha) * cos(theta);
		retVals(1,2) = -cos(theta) * sin(alpha);
		retVals(1,3) = a * sin(theta);

		retVals(2,0) = T(0.0);
		retVals(2,1) = sin(alpha);
		retVals(2,2) = cos(alpha);
		retVals(2,3) = d;

		retVals(3,0) = T(0.0);
		retVals(3,1) = T(0.0);
		retVals(3,2) = T(0.0);
		retVals(3,3) = T(1.0);

		return retVals;
	}

protected:
	void computeDH() {
		_mat = dhTransform(_a, _alpha, _d, _theta);
	}

	T _a, _alpha, _d, _theta;
	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> _mat;
};

#endif
