#ifndef CUDA_COLOR_SEG_INTERFACE_H
#define CUDA_COLOR_SEG_INTERFACE_H

//#include "ExternalQueuePair.h"
#include "FrameDesc.h"
#include "KinectFrame.h"
//#include "SimpleDLLControl.h"
#include "SimplePool.h"
//#include "TBEUQueue.h"
#include "TypeRecipientBroadcaster.h"
#include "UBCColorTrackerCUDA.cuh"

class CUDAColorSegInterface
	:
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> 
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr> {
public:
	CUDAColorSegInterface(
		//HINSTANCE cudaDLL, 
		int w, int h, int bpp
		, MarginalTrackerParams &mtp
		//, TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &q
	);
	~CUDAColorSegInterface();

	struct MarginalTrackerParams &getMTP();

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	MarginalTrackerParams &_mtp;
	CUDATracker _tracker;
};

#endif
