#include "KinectFilePlayer.h"
#include "KinectFrameFactory.h"
#include "KinectVideoDecompress.h"

KinectFilePlayer::KinectFilePlayer(
	int poolDepth
	, BodySegments &bs
	, TrackIDManager &tidm
	, ICoordinateMapper &cm
	, ProcessingParameters &pp
	) :
	_kvd(NULL) {
	_yuyFD.w = 1920;
	_yuyFD.h = 1080;
	_yuyFD.bpp = 2;

	_depthFD.w = 512;
	_depthFD.h = 424;
	_depthFD.bpp = 2;

	KinectFrameFactory kff(_yuyFD, _depthFD, bs, tidm, cm, pp);
	_framePool = new SimplePool<KinectFrame>(kff);
}

KinectFilePlayer::~KinectFilePlayer() {}

void KinectFilePlayer::open(wstring fileName) {
	if (_kvd) delete _kvd;
	_kvd = new KinectVideoDecompress(fileName, _yuyFD);
}

FrameDesc &KinectFilePlayer::getYUYFD() {
	return _yuyFD;
}

FrameDesc &KinectFilePlayer::getDepthFD() {
	return _depthFD;
}

/*
TrackIDManager &KinectFilePlayer::getTIDM() {
	return _tidm;
}
*/

SimplePool<KinectFrame> &KinectFilePlayer::getKFPool() {
	return *_framePool;
}

size_t KinectFilePlayer::getNVals() {
	return 1;
}

long KinectFilePlayer::get(long index) {
	return _kvd == NULL ? 0 : _kvd->nFrames();
}

void KinectFilePlayer::setProt(long index, long value) {
	SimplePool<KinectFrame>::PooledPtr kf = _framePool->getInstance();
	if (_kvd) {
		_kvd->fillInFrame(kf, value);
		TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::fireUpdate(kf);
		ExternalUpdateCollection::update();
	}
}

bool KinectFilePlayer::hasMin(long index) {
	return true;
}

bool KinectFilePlayer::hasMax(long index) {
	return true;
}

long KinectFilePlayer::getMinVal(long index) {
	return 0;
}

long KinectFilePlayer::getMaxVal(long index) {
	return _kvd == NULL ? 0 : (_kvd->nFrames() - 1);
}