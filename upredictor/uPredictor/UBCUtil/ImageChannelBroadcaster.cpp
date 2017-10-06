#include "ImageChannelBroadcaster.h"
#include "ImageChannelProvider.h"

ImageChannelBroadcaster::ImageChannelBroadcaster(
	long source, long index) : _source(source), _index(index) {}

ImageChannelBroadcaster::~ImageChannelBroadcaster() {}

void ImageChannelBroadcaster::processType(ImageChannelProvider *t) {
	fireUpdate(t->getImageChannel(_source._t, _index._t));
}

void ImageChannelBroadcaster::onStartup() {}