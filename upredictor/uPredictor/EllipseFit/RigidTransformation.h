#ifndef RIGID_TRANSFORMATION_H
#define RIGID_TRANSFORMATION_H

#include <Eigen/Core>

using namespace Eigen;

class RigidTransformation {
public:
	RigidTransformation();
	~RigidTransformation();

	void update(
		double rX, double rY, double rZ
		, double tX, double tY, double tZ);

	MatrixXd getMat();

protected:
	MatrixXd _rt;
};

#endif
