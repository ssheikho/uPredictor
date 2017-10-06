#ifndef DEPTH_VIDEO_PLAYBACK_H
#define DEPTH_VIDEO_PLAYBACK_H

#include "KinectDepthDecompress.h"
#include "KinectFrame.h"
#include "KinectFrameFactory.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <opencv2/opencv.hpp>

class DepthVideoPlayback : public TypeRecipient<long>
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>
{
public:
	DepthVideoPlayback(wstring fileName
		, BodySegments &bs
		, TrackIDManager &tidm
		, ProcessingParameters &pp);
	~DepthVideoPlayback();

	long getNFrames();

	// TypeRecipient
	void processType(long t);
	void onStartup();

protected:
	KinectDepthDecompress _kdd;

	KinectFrameFactory *_kff;
	IKinectSensor *_kinectSensor;
	FrameDesc _yuyFD, _depthFD;
	ICoordinateMapper *_coordinateMapper;

	SimplePool<KinectFrame> *_framePool;
};

#endif