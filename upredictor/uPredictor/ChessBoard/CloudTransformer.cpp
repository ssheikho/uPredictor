#include "CloudTransformer.h"

#include <iostream>

using namespace std;

CloudTransformer::CloudTransformer(Matrix4d rt) :
	_rt(rt) {}

CloudTransformer::~CloudTransformer() {}

void CloudTransformer::processType(SimplePool<KinectFrame>::PooledPtr t)
{
	ArrayPt3DCollection &pts = t->getRegisteredPts();

	for (int i = 0; i < pts.getNPts(); i++)
	{
		if (pts.getCameraPt(i)->X != pts.getCameraPt(i)->X) {
			// pts.getCameraPt(i)->X = pts.getCameraPt(i)->Y = pts.getCameraPt(i)->Z = 1000.0;
			continue;
		}

		CameraSpacePoint *csp = pts.getCameraPt(i);
		Matrix<double, 4, 1> pt;
		pt << csp->X, csp->Y, csp->Z, 1;
		//cout << pt.transpose() << endl;
		pt *= 1000.0;
		pt(3, 0) /= 1000.0;
		pt = _rt * pt;

		//cout << pt.transpose() << endl;
		pt /= 1000.0;
		*csp = {pt(0, 0), pt(1, 0), pt(2, 0)};
		pts.setCameraPt(i, *csp);

		//cout << pts.getCameraPt(i)->X << ", " << pts.getCameraPt(i)->Y << ", " << pts.getCameraPt(i)->Z << endl;
	}
/*	int nPts = pts.getNPts();

	MatrixXd points(4, nPts);
	for (int i = 0; i < nPts; i++)
	{
		CameraSpacePoint *csp = pts.getCameraPt(i);
		Vector4d pt;
		pt << csp->X, csp->Y, csp->Z, 1;
		points.col(i) = pt;
	}
	points.row(3) /= 1000.0;
	points = _rt * points;
	for (int i = 0; i< nPts; i++)
	{
		Vector4d pt = points.col(i);

		if (pt(0, 0) != pt(0, 0))
			continue;

		CameraSpacePoint csp = {pt(0, 0), pt(1, 0), pt(2, 0)};
		pts.setCameraPt(i, csp);
	}*/

	fireUpdate(t);
}

void CloudTransformer::onStartup() {}