#include "DepthVideoPlayback.h"
#include "UBCUtil.h"

DepthVideoPlayback::DepthVideoPlayback(wstring fileName
	, BodySegments &bs
	, TrackIDManager &tidm
	, ProcessingParameters &pp
	) :
	_coordinateMapper(NULL)
{
	_yuyFD = {1920, 1080, 2};
	_depthFD = {512, 424, 2};
	_kdd.open(fileName, _depthFD);

	_kff = new KinectFrameFactory(_yuyFD, _depthFD, bs, tidm, *_coordinateMapper, pp);
	_framePool = new SimplePool<KinectFrame>(*_kff, 100);
}

DepthVideoPlayback::~DepthVideoPlayback() {}

long DepthVideoPlayback::getNFrames()
{
	// Reading the last frame closes the stream.
	return _kdd.getNFrames() - 1;
}

void DepthVideoPlayback::processType(long t)
{
	if ((_framePool->poolDepth() < 20) || (_framePool->poolSize() > 0))
	{
		SimplePool<KinectFrame>::PooledPtr kf = _framePool->getInstance();
		kf->clear();

		_kdd.fillInFrame(kf, t);

		// TODO: Body tracking?
		fireUpdate(kf);
	}
}

void DepthVideoPlayback::onStartup() {}