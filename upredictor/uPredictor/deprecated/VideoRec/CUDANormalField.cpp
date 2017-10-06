#include "CUDANormalField.h"
#include "CUDAControl.h"

CUDANormalField::CUDANormalField(
	HINSTANCE cudaDLL, int dimX, int dimY
	, TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &q) :
	_cudaDLL(cudaDLL), _dimX(dimX), _dimY(dimY), _q(q) {
	_setupCloudNormalComp =
		(setupCloudNormalCompType)GetProcAddress(cudaDLL, "setupCloudNormalComp");

	_computeCloudNormals =
		(computeCloudNormalsType)GetProcAddress(cudaDLL, "computeCloudNormals");

	_computeFloatImage =
		(computeFloatImageType)GetProcAddress(cudaDLL, "computeFloatImage");

	_cccn = _setupCloudNormalComp(_dimX, _dimY, setDevice(_cudaDLL));
}

CUDANormalField::~CUDANormalField() {}

void CUDANormalField::processType(SimplePool<KinectFrame>::PooledPtr t) {
	Computer c(&_cccn, _computeCloudNormals);
	ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr> eqp(&c, t);
	_q.processType(eqp);
	eqp.waitUntilDone();
}

void CUDANormalField::onStartup() {}

CUDANormalField::Computer::Computer(CUDAComputeCloudNormals *cccn
	, computeCloudNormalsType computeCloudNormals) :
	_cccn(cccn)
	, _computeCloudNormals(computeCloudNormals) {}

CUDANormalField::Computer::~Computer() {}

void CUDANormalField::Computer::processType(
	SimplePool<KinectFrame>::PooledPtr t) {
	_computeCloudNormals(_cccn, t->_pts.getCameraPts()
		, (float *)t->_normVectsX.data, (float *)t->_normVectsY.data
		, (float *)t->_normsX.data, (float *)t->_normsY.data
		, (float *)t->_sinesX.data, (float *)t->_sinesY.data
		, (float *)t->_cosinesX.data, (float *)t->_cosinesY.data
	);
}

void CUDANormalField::Computer::onStartup() {}