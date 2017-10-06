#ifndef SEGMENT_BROADCASTER_H
#define SEGMENT_BROADCASTER_H

#include "KinectFrame.h"
#include "SimplePool.h"
#include <TypeBroadcaster.h>
#include <TypeRecipient.h>
#include <ValueListener.h>

#include <opencv/cv.hpp>

class SegmentBroadcaster :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<cv::Mat>
{
public:
	SegmentBroadcaster(size_t index);
	~SegmentBroadcaster();

	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

	size_t _index;

};

#endif
