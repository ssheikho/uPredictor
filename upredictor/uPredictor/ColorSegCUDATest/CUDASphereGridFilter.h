#ifndef CUDA_SPHERE_GRID_FILTER_H
#define CUDA_SPHERE_GRID_FILTER_H

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TBEUQueue.h"
#include "ThreeDBB.h"
#include "TypeRecipient.h"
#include "UBCColorTrackerCUDA.cuh"

class CUDASphereGridFilter :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	CUDASphereGridFilter(
		//HINSTANCE cudaDLL, 
		int segmentNumber, int nPts);
	~CUDASphereGridFilter();

	//TypeRecipient
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	int _segmentNumber, _nPts;
	GridParams _gp;
	CUDASphereDetector _csd;
};

#endif
