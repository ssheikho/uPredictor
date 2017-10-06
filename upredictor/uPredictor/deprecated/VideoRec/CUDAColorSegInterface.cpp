#include "CUDAColorSegInterface.h"
#include "CUDAControl.h"

CUDAColorSegInterface::CUDAColorSegInterface(
	HINSTANCE cudaDLL, int w, int h, int bpp
	, TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &q) :
	_cudaDLL(cudaDLL), _q(q) {
	//_mtp._sizeII = w * h * bpp;
	_mtp._nchans = 3;
	_mtp._npix = w * h;
	_mtp._sizeII = _mtp._npix * _mtp._nchans;
	_mtp._mostlyChan = 0;
	_mtp._fromChanA = 1;
	_mtp._fromChanB = 2;
	_mtp._marginA = 40;
	_mtp._marginB = 65;
	_mtp._indicColorB = 255;
	_mtp._indicColorG = 0;
	_mtp._indicColorR = 255;

	_doSetupCUDATracker =
		(doSetupCUDATrackerType)GetProcAddress(cudaDLL, "setupCUDATracker");

	_doMarginalSegmentation =
		(doMargSegType)GetProcAddress(cudaDLL, "doMarginalSegmentationSimple");

	_tracker = _doSetupCUDATracker(&_mtp, setDevice(_cudaDLL));


}

CUDAColorSegInterface::~CUDAColorSegInterface() {}

struct MarginalTrackerParams &CUDAColorSegInterface::getMTP() {
	return _mtp;
}

void CUDAColorSegInterface::processType(SimplePool<KinectFrame>::PooledPtr t) {
	Computer c(&_mtp, _doMarginalSegmentation);
	ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr> eqp(&c, t);
	_q.processType(eqp);
	eqp.waitUntilDone();
}

void CUDAColorSegInterface::onStartup() {}

CUDAColorSegInterface::Computer::Computer(MarginalTrackerParams *tracker
	, doMargSegType doMarginalSegmentation) :
	_tracker(tracker)
	, _doMarginalSegmentation(doMarginalSegmentation) {}

CUDAColorSegInterface::Computer::~Computer() {}

void CUDAColorSegInterface::Computer::processType(
	SimplePool<KinectFrame>::PooledPtr t) {
	_doMarginalSegmentation(_tracker
		, t->_pts.getBGRImage().data, t->_depthSegImg.data);
}

void CUDAColorSegInterface::Computer::onStartup() {}