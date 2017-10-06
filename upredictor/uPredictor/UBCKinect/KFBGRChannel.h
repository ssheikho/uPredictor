#ifndef KF_BGR_CHANNEL_H
#define KF_BGR_CHANNEL_H

#include "KinectFrame.h"
#include "RefCountedPtr.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <opencv/cv.hpp>

class KFBGRChannel :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>,
	public TypeBroadcaster<cv::Mat> {
public:
	KFBGRChannel(long source, long chan);
	~KFBGRChannel();

	void processType(SimplePool<KinectFrame>::PooledPtr inObj);
	void onStartup();

protected:
	long _source, _chan;
};

#endif