#ifndef ELLIPSE3D_H
#define ELLIPSE3D_H

#include "Ellipse.h"
#include "EllipseImplicitFit.h"
#include "EllipseThetaMin.h"

#include <Eigen/Dense>

template<typename T>
class Ellipse3D {
public:
	Ellipse3D(MatrixXd inPtsAlongCols) :
		_eif(inPtsAlongCols),
		_ellipse(_eif) {}

	~Ellipse3D() {}

	EllipseImplicitFit<T> getEIF() {
		return _eif;
	}

	Ellipse getEllipse() {
		return _ellipse;
	}

	MatrixXd getPointAtThetaH(double theta) {
		return	cart3DRotMatToHomRT(_eif.getRotToXY().transpose()) *
				twoDHomToThreeDHom(_ellipse.getPointAtThetaH(theta)
					, -_eif.getPlane().getPlaneN()(3));
	}

	MatrixXd getPointAtThetasH(MatrixXd thetas) {
		return	cart3DRotMatToHomRT(_eif.getRotToXY().transpose()) *
				twoDHomToThreeDHom(_ellipse.getPointAtThetasH(thetas)
					, -_eif.getPlane().getPlaneN()(3));
	}

	pair<double, double> findOneTheta(double startTheta, double x, double y) {
		pair<double, double> retVal;
		retVal.second = startTheta;
		ceres::CostFunction *cf =
			EllipseThetaMin::Create(
			_ellipse.getRT2D().getCX()
			, _ellipse.getRT2D().getCY()
			, _ellipse.getRT2D().getTheta()
			, _ellipse.getA()
			, _ellipse.getB()
			, x, y);

		ceres::Problem problem;
		problem.AddResidualBlock(cf,
			NULL /* squared loss */,
			&retVal.second);

		ceres::Solver::Options options;
		ceres::Solver::Summary summary;

		ceres::Solve(options, &problem, &summary);
		retVal.first = summary.final_cost;
		return retVal;
	}

	pair<double, double> findOneThetaQuad(
		double &startTheta, double x, double y) {
		double incr = M_PI / 2.0;

		pair<double, double> a = findOneTheta(startTheta, x, y);
		pair<double, double> b = findOneTheta(startTheta + incr, x, y);
		pair<double, double> c = findOneTheta(startTheta + incr * 2.0, x, y);
		pair<double, double> d = findOneTheta(startTheta + incr * 3.0, x, y);

		a = a.first < b.first ? a : b;
		c = c.first < d.first ? c : d;

		return a.first < c.first ? a : c;
	}

	MatrixXd findThetas() {
		Matrix<double, Dynamic, Dynamic> pts =_eif.getPtsXYAlongCols();

		size_t cols = pts.cols();
		MatrixXd thetas(1,cols);
		thetas(0,0) = (double)rand() / (double)RAND_MAX * M_PI * 2.0 - M_PI;
		pair<double, double> a =
			findOneThetaQuad(thetas(0,0), pts(0,0), pts(1,0));
		thetas(0,0) = a.second;
		for(size_t i = 1; i < cols; i++) {
			double startTheta = thetas(0,i-1);
			a = findOneThetaQuad(startTheta, pts(0,i), pts(1,i));
			thetas(0,i) = a.second;
		}

		return thetas;
	}

protected:
	EllipseImplicitFit<T> _eif;
	Ellipse _ellipse;
};

#endif
