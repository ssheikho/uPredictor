#include "SegmentBroadcaster.h"

SegmentBroadcaster::SegmentBroadcaster(size_t index) : _index(index) {}

SegmentBroadcaster::~SegmentBroadcaster() {}

void SegmentBroadcaster::processType(SimplePool<KinectFrame>::PooledPtr t) {
	fireUpdate(t->_sdi._depthSegImg);
}

void SegmentBroadcaster::onStartup() {}