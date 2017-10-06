#ifndef NAIVE_IK_H
#define NAIVE_IK_H

#include "BasicFormulas.h"
#include "ForwardKin.h"
#include <UBCUtil.h>

#include "ceres/ceres.h"

#include <iostream>
#include <vector>

template <typename T>
struct NaiveIK {
	NaiveIK(ForwardKin<T> &fk
		, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> pos,
		T parametricTerm,
		std::vector<T> jointMinAngles,
		std::vector<T> jointMaxAngles
		) :
		_fk(fk)
		, _pos(pos)
		, _origin(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>(4,1))
		, _parametricTerm(parametricTerm)
		, _jointMinAngles(jointMinAngles)
		, _jointMaxAngles(jointMaxAngles)
		 {
		_origin << 0.0, 0.0, 0.0, 1.0;
	}

	template <typename U>
	bool operator()(const U* const candidateParam, U* residuals) const {
		U *thetas = new U[_fk.getNJoints()];
	
		for(size_t i = 0; i < _fk.getNJoints(); i++) {
			size_t iTimesFour = i * 4;
			thetas[i] = 
				simpleThirdOrder(
					candidateParam[iTimesFour]
					, candidateParam[iTimesFour + 1]
					, candidateParam[iTimesFour + 2]
					, candidateParam[iTimesFour + 3]
					, _parametricTerm);
		}

		for(size_t i = 0; i < _fk.getNJoints(); i++)
			_fk.getDH(i).setTheta(thetas[i]);

		Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> a =
			homToCart(_fk.getMat(_fk.getNJoints()) * _origin);

		/*
		double res[3];   
		residuals[0] = sqrt(res[0]*res[0] + 
			res[1]*res[1] + res[2]*res[2]);
		
		residuals[0] =  a(0,0) - _pos(0,0);
		residuals[1] =  a(1,0) - _pos(1,0);
		residuals[2] =  a(2,0) - _pos(2,0);

		residuals[0] = sqrt(res[0]*res[0] + 
			res[1]*res[1] + res[2]*res[2]);

		*/

		residuals[0] = a(0,0) - _pos(0,0);
		residuals[1] = a(1,0) - _pos(1,0);
		residuals[2] = a(2,0) - _pos(2,0);
	
		bool retVal = true;
		for(size_t i = 0; i < _fk.getNJoints(); i++) {
			retVal =  retVal && (thetas[i] >= _jointMinAngles[i]);
			retVal =  retVal && (thetas[i] <= _jointMaxAngles[i]);
		}
		
	
		return true;
	}

	// Factory to hide the construction of the CostFunction object from
	// the client code.
	static ceres::CostFunction* CreateThirdOrderSevenParam(
		ForwardKin<T> &fk
		, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> pos
		, T parametricTerm
		, std::vector<T> jointMinAngles
		, std::vector<T> jointMaxAngles) {
		return
			new ceres::NumericDiffCostFunction<NaiveIK, ceres::CENTRAL, 3, 28>(
			new NaiveIK(
				fk, pos, parametricTerm
				, jointMinAngles
				, jointMaxAngles));
	}

	ForwardKin<T> &_fk;
	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> _pos, _origin;
	T _parametricTerm;
	std::vector<T> _jointMinAngles, _jointMaxAngles;
};

#endif 
