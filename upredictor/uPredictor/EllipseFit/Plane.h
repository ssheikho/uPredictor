#ifndef PLANE_H
#define PLANE_H

#include <Eigen/Core>

using namespace Eigen;

class Plane {
public:
	//Points assumed to be Cartesian, 1 point per row
	Plane(MatrixXd inPts);
	~Plane();

	Vector4d getPlane();
	Vector3d getPlaneNormalVect();
	double getNorm();
	Vector4d getPlaneN();
	Vector3d getPlaneNormalVectN();
	


protected:
	Vector4d _plane;
	Vector3d _planeNormalVect;
	double _norm;
	Vector4d _planeN;
	Vector3d _planeNormalVectN;
};

#endif
