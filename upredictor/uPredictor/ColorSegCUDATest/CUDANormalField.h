#ifndef CUDA_NORMAL_FIELD_H
#define CUDA_NORMAL_FIELD_H

#include "ExternalQueuePair.h"
#include "KinectFrame.h"
#include "SimpleDLLControl.h"
#include "SimplePool.h"
#include "TBEUQueue.h"
#include "TypeRecipient.h"
#include "UBCColorTrackerCUDA.cuh"

class CUDANormalField :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	CUDANormalField(
		//HINSTANCE cudaDLL,
		int dimX, int dimY, int nChans
	//	, TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &q
	);
	~CUDANormalField();

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	class Computer :
		public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
	public:
		Computer(
			CUDAComputeCloudNormals *cccn
			, CUDAComputeFloatToImage *ccfti
			//, computeCloudNormalsType computeCloudNormals
			//, computeFloatImageType computeFloatImage
			);
		~Computer();

		void processType(SimplePool<KinectFrame>::PooledPtr t);
		void onStartup();

	protected:
		CUDAComputeCloudNormals *_cccn;
		CUDAComputeFloatToImage *_ccfti;
		//computeCloudNormalsType _computeCloudNormals;
		//computeFloatImageType _computeFloatImage;
	};

	//HINSTANCE _cudaDLL;
	int _dimX, _dimY;
	//TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &_q;

	CUDAComputeCloudNormals _cccn;
	CUDAComputeFloatToImage _ccfti;

	//setupCloudNormalCompType _setupCloudNormalComp;
	//setupCUDAComputeFloatImageType _setupCUDAComputeFloatImage;

	//computeCloudNormalsType _computeCloudNormals;
	//computeFloatImageType _computeFloatImage;
};

#endif