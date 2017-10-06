#ifndef ELLIPSE_COST_FUNCTION_H
#define ELLIPSE_COST_FUNCTION_H

#include "ceres/ceres.h"

struct EllipseCostFunction {
	EllipseCostFunction(
		double x, double y, double z
		, int ptNo
		) : _x(x), _y(y), _z(z), _ptNo(ptNo) {}

	template <typename T> bool operator()(
		const T* rot, const T* trans,  const T* alphaBeta
		, const T* thetas, T* residuals) const {
		/*
		T p[3];
		ceres::AngleAxisRotatePoint(camera, point, p);
		// camera[3,4,5] are the translation.
		p[0] += camera[3]; p[1] += camera[4]; p[2] += camera[5];

		// Compute the center of distortion. The sign change comes from
		// the camera model that Noah Snavely's Bundler assumes, whereby
		// the camera coordinate system has a negative z axis.
		T xp = - p[0] / p[2];
		T yp = - p[1] / p[2];

		// Apply second and fourth order radial distortion.
		const T& l1 = camera[7];
		const T& l2 = camera[8];
		T r2 = xp*xp + yp*yp;
		T distortion = T(1.0) + r2  * (l1 + l2  * r2);

		// Compute final projected point position.
		const T& focal = camera[6];
		T predicted_x = focal * distortion * xp;
		T predicted_y = focal * distortion * yp;

		// The error is the difference between the predicted and observed position.
		residuals[0] = predicted_x - T(observed_x);
		residuals[1] = predicted_y - T(observed_y);
		*/
		return true;
	}

   // Factory to hide the construction of the CostFunction object from
   // the client code.
	static ceres::CostFunction* Create(
		const double x, const double y, const double z, const int sampleNo) {
		return (
			new ceres::AutoDiffCostFunction<
				EllipseCostFunction, 1, 3, 3, 2>(
				new EllipseCostFunction(x, y, z, sampleNo)));
	}

	double _x, _y, _z;
	int _ptNo;
};

#endif
