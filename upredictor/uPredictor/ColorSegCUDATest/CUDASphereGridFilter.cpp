#include "CUDASphereGridFilter.h"

#include "cuda.h"
#include "cuda_runtime.h"

#include <fstream>

CUDASphereGridFilter::CUDASphereGridFilter(
	//HINSTANCE cudaDLL,
	int segmentNumber, int nPts) :
	_segmentNumber(segmentNumber)
	, _nPts(nPts) {

	_gp._r = 0.04;
	_gp._gridDim = 10;
	_gp._nPts = nPts;

	_csd = setupCUDAGridFilter(&_gp);

}

CUDASphereGridFilter::~CUDASphereGridFilter() {}

void CUDASphereGridFilter::processType(SimplePool<KinectFrame>::PooledPtr t) {
	t->_sdi._threeDBB.update(
		t->_sdi._depthSegMap
		, t->_pts.getCameraPts()
		, _nPts
		, _segmentNumber);

	resizeGrid(
		t->_sdi._threeDBB._minX3D, t->_sdi._threeDBB._maxX3D
		, t->_sdi._threeDBB._minY3D, t->_sdi._threeDBB._maxY3D
		, t->_sdi._threeDBB._minZ3D, t->_sdi._threeDBB._maxZ3D
		, &_csd
	);

	computeCosts(t->_pts.getCameraPts(), t->_sdi._depthSegMap, _segmentNumber
		, &_csd);

	t->_sdi.update(_gp, _csd._hostCenters);
}

void CUDASphereGridFilter::onStartup() {

}