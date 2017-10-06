#ifndef CUDA_COLOR_SEG_INTERFACE_H
#define CUDA_COLOR_SEG_INTERFACE_H

#include "ExternalQueuePair.h"
#include "FrameDesc.h"
#include "KinectFrame.h"
#include "SimpleDLLControl.h"
#include "SimplePool.h"
#include "TBEUQueue.h"
#include "TypeRecipientBroadcaster.h"
#include "UBCColorTrackerCUDA.h"

extern "C" {
	typedef CUDATracker(CALLBACK* doSetupCUDATrackerType)
		(struct MarginalTrackerParams *marginalTrackerParams, int stream);

	typedef int (CALLBACK* doMargSegType)(
		struct MarginalTrackerParams *marginalTrackerParams
		, unsigned char *inputImage
		, unsigned char *outputImage);
}


class CUDAColorSegInterface
	:
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	CUDAColorSegInterface(HINSTANCE cudaDLL, int w, int h, int bpp
		, TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &q);
	~CUDAColorSegInterface();

	struct MarginalTrackerParams &getMTP();

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	class Computer :
		public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
	public:
		Computer(MarginalTrackerParams *tracker
			, doMargSegType doMarginalSegmentation);
		~Computer();

		void processType(SimplePool<KinectFrame>::PooledPtr t);
		void onStartup();

	protected:
		MarginalTrackerParams *_tracker;
		doMargSegType _doMarginalSegmentation;
	};

	HINSTANCE _cudaDLL;
	TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &_q;
	struct MarginalTrackerParams _mtp;
	struct CUDATracker _tracker;
	doSetupCUDATrackerType _doSetupCUDATracker;
	doMargSegType _doMarginalSegmentation;
};

#endif