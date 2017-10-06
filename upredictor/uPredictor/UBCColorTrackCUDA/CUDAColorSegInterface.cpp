#include "CUDAColorSegInterface.h"
//#include "CUDAControl.h"

CUDAColorSegInterface::CUDAColorSegInterface(
	int w, int h, int bpp
	, struct MarginalTrackerParams &mtp) : _mtp(mtp) {
	_mtp._nchans = 3;
	_mtp._npix = w * h;
	_mtp._sizeII = _mtp._npix * _mtp._nchans;
	_mtp._mostlyChan = 2;
	_mtp._fromChanA = 1;
	_mtp._fromChanB = 0;
	_mtp._marginA = 0;
	_mtp._marginB = 0;
	_mtp._indicColorB = 255;
	_mtp._indicColorG = 0;
	_mtp._indicColorR = 255;

	_tracker = setupCUDATracker(&_mtp, setDevice());
}

CUDAColorSegInterface::~CUDAColorSegInterface() {}

struct MarginalTrackerParams &CUDAColorSegInterface::getMTP() {
	return _mtp;
}

void CUDAColorSegInterface::processType(SimplePool<KinectFrame>::PooledPtr t) {
	//cout	<< "_mtp._mostlyChan:	" << _mtp._mostlyChan << endl
	//		<< "_mtp._fromChanA:	" << _mtp._fromChanA << endl
	//		<< "_mtp._fromChanB:	" << _mtp._fromChanB << endl;

	doMarginalSegmentation(
		&_tracker
		, t->_pts.getBGRImage().data
		, t->_sdi._depthSegImg.data
		, t->_sdi._depthSegMap);

	fireUpdate(t);
}

void CUDAColorSegInterface::onStartup() {}
