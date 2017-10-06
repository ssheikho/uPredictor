#ifndef SPHERE_FIT_COST_FUNCTOR_H
#define SPHERE_FIT_COST_FUNCTOR_H

#include "Point3DRGB.h"
#include "Pt3DCollection.h"
//#include "UBCSphere.h"

//#include <boost/scoped_ptr.hpp>

//#include <vector>

//using namespace boost;
using namespace std;

struct SphereFitCostFunctor {
protected:
	Pt3DCollection *_pts;

public:
	SphereFitCostFunctor(Pt3DCollection *pts = NULL) :
		_pts(pts) {}

	~SphereFitCostFunctor() {}

	void setPtCollection(Pt3DCollection *pts) {
		_pts = pts;
	}

	template<typename T>
	T ptDistToSphere(
		int ptIndex
		, T const *cx
		, T const *cy
		, T const *cz
		, T const *r) const {
		CameraSpacePoint *p = _pts->getCameraPt(ptIndex);
		//T xx = T(p->_x3D) - *cx;
		//T yy = T(p->_y3D) - *cy;
		//T zz = T(p->_z3D) - *cz;
		T xx = T(p->X) - *cx;
		T yy = T(p->Y) - *cy;
		T zz = T(p->Z) - *cz;
		xx *= xx;
		yy *= yy;
		zz *= zz;
		T signedDist = sqrt(xx + yy + zz) - *r;
		return signedDist;// >= 0.0 ? signedDist : -signedDist;
	}

	template<typename T>
	bool operator()(
		T const *cx
		, T const *cy
		, T const *cz
		, T const *r
		, T* residuals) const {
		int nPts = _pts->getNPts();
		for (int i = 0; i < nPts; i++) {
			residuals[i] = ptDistToSphere(i, cx, cy, cz, r);
		}
		return true;
	}

};

#endif