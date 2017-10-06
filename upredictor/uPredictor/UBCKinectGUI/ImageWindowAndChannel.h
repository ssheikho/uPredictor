#ifndef IMAGE_WINDOW_AND_CHANNEL_H
#define IMAGE_WINDOW_AND_CHANNEL_H

#include "ImageWindow.h"
#include "KFBGRChannel.h"

class ImageWindowAndChannel {
public:
	ImageWindowAndChannel(
		LayoutContainer *parent, int w, int h, string name
		, long source, long chan
		, double xClickMultiplier = 1.0, double yClickMultiplier = 1.0);
	~ImageWindowAndChannel();

	KFBGRChannel &getChan();
	
protected:
	ImageWindow _iw;
	KFBGRChannel _chan;
};

#endif
