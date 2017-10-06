#include "KinectPlaybackInterface.h"

KinectPlaybackInterface::KinectPlaybackInterface(
	wstring fileName
	, BodySegments &bs
	, TrackIDManager &tidm
	, ProcessingParameters &pp
	) :
	_bs(&bs)
	, _tidm(&tidm)
	, _cm(NULL)
	, _pp(&pp)
{
	// Initialize the FrameDesc's
	_yuyFD.w = 1920;
	_yuyFD.h = 1080;
	_yuyFD.bpp = 2;

	_depthFD.w = 512;
	_depthFD.h = 424;
	_depthFD.bpp = 2;

	// Initialize the decompressors
	_kdd = new KinectDepthDecompress(fileName, _depthFD);
	_kvd = new KinectVideoDecompress(fileName + L".avi", _yuyFD);

	// Initialize the frame pool
	_kff = new KinectFrameFactory(
		_yuyFD, _depthFD, *_bs, *_tidm, *_cm, *_pp);
	_framePool = new SimplePool<KinectFrame>(*_kff, 100);
}

KinectPlaybackInterface::~KinectPlaybackInterface() {}

void KinectPlaybackInterface::processType(long t)
{
	if ((_framePool->poolDepth() < 20) || (_framePool->poolSize() > 0))
	{
		SimplePool<KinectFrame>::PooledPtr kf = _framePool->getInstance();
		kf->clear();

		_kvd->fillInFrame(kf, t);
		_kdd->fillInFrame(kf, t);

		fireUpdate(kf);
	}
}

void KinectPlaybackInterface::onStartup() {}

long KinectPlaybackInterface::getYUYNFrames() { return _kvd->nFrames(); }
long KinectPlaybackInterface::getDepthNFrames() { return _kdd->getNFrames(); }

FrameDesc &KinectPlaybackInterface::getYUYFD() { return _yuyFD; }
FrameDesc &KinectPlaybackInterface::getDepthFD() { return _depthFD; }

SimplePool<KinectFrame> &KinectPlaybackInterface::getKFPool()
{
	return *_framePool;
}