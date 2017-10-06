#ifndef KI_DEPTH_SOURCE_H
#define KI_DEPTH_SOURCE_H

#include "KinectFrame.h"
#include "SimplePool.h"

#include "depth_sources/depth_source.h"

#include <opencv/cv.h>

class CameraModel;
struct FrameDesc;

class KIDepthSource :
	public dart::DepthSource<float, uchar3>
	, public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	KIDepthSource(
		SimplePool<KinectFrame>::PooledPtr kinectFrame
		, FrameDesc &fd
		, CameraModel &cm);
	~KIDepthSource();

	void processType(SimplePool<KinectFrame>::PooledPtr kinectFrame);
	void onStartup();

	//DepthSourceBase
	uint getFrame() const;
	void setFrame(const uint frame);
	void advance();

	bool hasRadialDistortionParams() const;
	const float * getRadialDistortionParams();

	//DepthSource<unsigned int, uchar3>
	const float *getDepth();
	const float *getDeviceDepth();

	const uchar3 *getColor();

	float getScaleToMeters() const { return 1.0f/1000.0f; }

protected:
	SimplePool<KinectFrame>::PooledPtr _kinectFrame;
	FrameDesc &_fd;
	float *_deviceDepth;
};

#endif
