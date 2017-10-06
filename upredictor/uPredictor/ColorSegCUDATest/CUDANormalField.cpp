#include "CUDANormalField.h"
#include "CUDAControl.h"

CUDANormalField::CUDANormalField(
	//HINSTANCE cudaDLL,
	int dimX, int dimY, int nChans
	//, TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &q
) :
	//_cudaDLL(cudaDLL),
	_dimX(dimX), _dimY(dimY)
	//, _q(q)
{
	//_setupCloudNormalComp =	(setupCloudNormalCompType)
	//	GetProcAddress(cudaDLL, "setupCloudNormalComp");
	//_setupCUDAComputeFloatImage = (setupCUDAComputeFloatImageType)
	//	GetProcAddress(cudaDLL, "setupCUDAComputeFloatImage");

	//_computeCloudNormals =
	//	(computeCloudNormalsType)GetProcAddress(cudaDLL, "computeCloudNormals");

	//_computeFloatImage =
	//	(computeFloatImageType)GetProcAddress(cudaDLL, "computeFloatImage");

	_cccn = setupCloudNormalComp(_dimX, _dimY, setDevice());
	_ccfti = setupCUDAComputeFloatImage(_dimX * _dimY, nChans);

}

CUDANormalField::~CUDANormalField() {}

void CUDANormalField::processType(SimplePool<KinectFrame>::PooledPtr t) {
	//Computer c(&_cccn, &_ccfti, _computeCloudNormals, _computeFloatImage);
	//ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr> eqp(&c, t);
	//_q.processType(eqp);
	//eqp.waitUntilDone();
	//eqp.update();

	computeCloudNormals(&_cccn, t->_pts.getCameraPts()
		, (float *)t->_normVectsX.data, (float *)t->_normVectsY.data
		, (float *)t->_normsX.data, (float *)t->_normsY.data
		, (float *)t->_sinesX.data, (float *)t->_sinesY.data
		, (float *)t->_cosinesX.data, (float *)t->_cosinesY.data
	);
}

void CUDANormalField::onStartup() {}

CUDANormalField::Computer::Computer(
	CUDAComputeCloudNormals *cccn
	, CUDAComputeFloatToImage *ccfti
	//, computeCloudNormalsType computeCloudNormals
	//, computeFloatImageType computeFloatImage
	) :
	_cccn(cccn)
	, _ccfti(ccfti)
	//, _computeCloudNormals(computeCloudNormals)
	//, _computeFloatImage(computeFloatImage)
{}

CUDANormalField::Computer::~Computer() {}

void CUDANormalField::Computer::processType(
	SimplePool<KinectFrame>::PooledPtr t) {
	computeCloudNormals(_cccn, t->_pts.getCameraPts()
		, (float *)t->_normVectsX.data, (float *)t->_normVectsY.data
		, (float *)t->_normsX.data, (float *)t->_normsY.data
		, (float *)t->_sinesX.data, (float *)t->_sinesY.data
		, (float *)t->_cosinesX.data, (float *)t->_cosinesY.data
	);

	//double minVal, maxVal;
	//cv::Point minLoc, maxLoc;
	//minMaxLoc(t->_normsX, &minVal, &maxVal, &minLoc, &maxLoc);

	computeFloatImage((float *)t->_sinesX.data, (char *)t->_sinesXBGR.data, _ccfti);
	computeFloatImage((float *)t->_sinesY.data, (char *)t->_sinesYBGR.data, _ccfti);

	//for (int i = 0; i < 10000; i++) t->_sinesXBGR.data[i] = 255;
	//_computeFloatImage((float *)t->_sinesY.data, (char *)t->_sinesYBGR.data, _ccfti);
	//_computeFloatImage((float *)t->_cosinesX.data, (char *)t->_cosinesXBGR.data, _ccfti);
	//_computeFloatImage((float *)t->_cosinesY.data, (char *)t->_cosinesYBGR.data, _ccfti);
}

void CUDANormalField::Computer::onStartup() {}