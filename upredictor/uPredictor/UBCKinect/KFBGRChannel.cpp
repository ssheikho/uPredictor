#include "KFBGRChannel.h"

KFBGRChannel::KFBGRChannel(long source, long chan) : _source(source), _chan(chan) {}

KFBGRChannel::~KFBGRChannel() {}

void KFBGRChannel::processType(SimplePool<KinectFrame>::PooledPtr inObj) {
	fireUpdate(inObj->getImageChannel(_source, _chan));
}

void KFBGRChannel::onStartup() {}