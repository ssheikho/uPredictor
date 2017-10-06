#include "ImageWindowAndChannel.h"

ImageWindowAndChannel::ImageWindowAndChannel(
	LayoutContainer *parent, int w, int h, string name
	, long source, long chan
	, double xClickMultiplier, double yClickMultiplier) :
	_iw(parent, w, h, name)
	, _chan(source, chan)
{
	_chan.addRecipient(&_iw);
}

ImageWindowAndChannel::~ImageWindowAndChannel() {}

KFBGRChannel &ImageWindowAndChannel::getChan() {
	return _chan;
}
