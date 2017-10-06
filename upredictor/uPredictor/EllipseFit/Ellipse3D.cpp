#include "Ellipse3D.h"
#include "Ellipse.h"
//#include "EllipseThetaMin.h"
#include "FitFunctions.h"

Ellipse3D::Ellipse3D(Eigen::MatrixXd inPtsAlongCols)

Ellipse3D::~Ellipse3D() {}

EllipseImplicitFit Ellipse3D::getEIF() {
	return _eif;
}

Ellipse Ellipse3D::getEllipse() {
	return _ellipse;
}

MatrixXd Ellipse3D::getPointAtThetaH(double theta) {
	return	cart3DRotMatToHomRT(_eif.getRotToXY().transpose()) *
			twoDHomToThreeDHom(_ellipse.getPointAtThetaH(theta)
				, -_eif.getPlane().getPlaneN()(3));
}

MatrixXd Ellipse3D::getPointAtThetasH(MatrixXd thetas) {
	return	cart3DRotMatToHomRT(_eif.getRotToXY().transpose()) *
			twoDHomToThreeDHom(_ellipse.getPointAtThetasH(thetas)
				, -_eif.getPlane().getPlaneN()(3));
}

MatrixXd Ellipse3D::findThetas() {
	//EllipseThetaMin etm(_ellipse, 0, 0);
}
