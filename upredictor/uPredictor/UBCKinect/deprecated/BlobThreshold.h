#ifndef BLOB_THRESHOLD_H
#define BLOB_THRESHOLD_H

#define GLOG_NO_ABBREVIATED_SEVERITIES

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

class BlobThreshold :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	BlobThreshold();
	~BlobThreshold();

	//TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);

};

#endif