#ifndef IMAGE_CHANNEL_BROADCASTER_H
#define IMAGE_CHANNEL_BROADCASTER_H

#include "TypeBroadcaster.h"
#include "TypeRecipient.h"
#include "ValueListener.h"

#include <opencv/cv.hpp>

class ImageChannelProvider;

class ImageChannelBroadcaster :
	public TypeRecipient<ImageChannelProvider *>
	, public TypeBroadcaster<cv::Mat> {
public:
	ImageChannelBroadcaster(long source, long index);
	~ImageChannelBroadcaster();

	void processType(ImageChannelProvider *t);
	void onStartup();
	
	ValueListener<long> _source, _index;

};

#endif
