#ifndef KINECT_PLAYBACK_INTERFACE_H
#define KINECT_PLAYBACK_INTERFACE_H

#include "KinectDepthDecompress.h"
#include "KinectFrame.h"
#include "KinectFrameFactory.h"
#include "KinectVideoDecompress.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

class KinectPlaybackInterface : public TypeRecipient<long>
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>
{
public:
	KinectPlaybackInterface(
		wstring fileName
		, BodySegments &bs
		, TrackIDManager &tidm
		, ProcessingParameters &pp
	);
	~KinectPlaybackInterface();

	// TypeRecipient
	void processType(long t);
	void onStartup();

	long getYUYNFrames();
	long getDepthNFrames();

	FrameDesc &getYUYFD();
	FrameDesc &getDepthFD();
	SimplePool<KinectFrame> &getKFPool();

protected:
	FrameDesc _yuyFD, _depthFD;
	BodySegments *_bs;
	TrackIDManager *_tidm;
	ICoordinateMapper *_cm;
	ProcessingParameters *_pp;

	KinectDepthDecompress *_kdd;
	KinectVideoDecompress *_kvd;

	ICoordinateMapper *_coordinateMapper;
	KinectFrameFactory *_kff;
	SimplePool<KinectFrame> *_framePool;
};

#endif