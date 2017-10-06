#ifndef CUDA_NORMAL_FIELD_H
#define CUDA_NORMAL_FIELD_H

#include "ExternalQueuePair.h"
#include "KinectFrame.h"
#include "SimpleDLLControl.h"
#include "SimplePool.h"
#include "TBEUQueue.h"
#include "TypeRecipient.h"
#include "UBCColorTrackerCUDA.h"

extern "C" {
	typedef CUDAComputeCloudNormals(CALLBACK* setupCloudNormalCompType)	(
		int dimX, int dimY, int stream);

	typedef void (CALLBACK* computeCloudNormalsType)(
		struct CUDAComputeCloudNormals *ct
		, CameraSpacePoint *camPts
		, float *outVectsX, float *outVectsY
		, float *outNormsX, float *outNormsY
		, float *outSinesX, float *outSinesY
		, float *outCosinesX, float *outCosinesY);

	typedef CUDAComputeFloatToImage(CALLBACK* computeFloatImageType)	(
		float *inFloat, char *outImg, CUDAComputeFloatToImage *cccn);
}

class CUDANormalField :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	CUDANormalField(
		HINSTANCE cudaDLL, int dimX, int dimY
		, TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &q);
	~CUDANormalField();

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	class Computer :
		public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
	public:
		Computer(CUDAComputeCloudNormals *cccn
			, computeCloudNormalsType computeCloudNormals);
		~Computer();

		void processType(SimplePool<KinectFrame>::PooledPtr t);
		void onStartup();

	protected:
		CUDAComputeCloudNormals *_cccn;
		computeCloudNormalsType _computeCloudNormals;
	};

	HINSTANCE _cudaDLL;
	int _dimX, _dimY;
	TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> &_q;
	CUDAComputeCloudNormals _cccn;;
	setupCloudNormalCompType _setupCloudNormalComp;
	computeCloudNormalsType _computeCloudNormals;
	computeFloatImageType _computeFloatImage;
};

#endif