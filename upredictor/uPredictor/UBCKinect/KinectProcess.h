#ifndef KINECT_PROCESS_H
#define KINECT_PROCESS_H

#include "KinectFrame.h"
//#include "PipelineProcess.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

enum KinectProcessType {
	KP_CONVERT_YUV_2_BGR,
	KP_CONVERT_DEPTH_2_BGR,
	KP_COMPUTE_DEPTH_L,
	KP_CONVERT_DEPTH_L_2_BGR,
	KP_COMPUTE_BODY_CAMERA_SPACE_PTS,
	KP_COMPUTE_BODY_COLOR_SPACE_PTS,
	KP_COMPUTE_BODY_DEPTH_SPACE_PTS,
	KP_RENDER_BODY_ON_HD_BGR_IMAGE,
	KP_RENDER_BODY_ON_DEPTH_BGR_IMAGE,
	KP_COMPUTE_DEPTH_CAMERA_SPACE_PTS,
	KP_COMPUTE_DEPTH_COLOR_SPACE_PTS,
	KP_COMPUTE_PT_REGISTRATION,
	KP_COMPUTE_DEPTH_32_FC1,
	KP_COMPUTE_DEPTH_32_FC1_BLUR,
	KP_COMPUTE_DEPTH_32_FC1_GRADX,
	KP_COMPUTE_DEPTH_32_FC1_GRADY,
	KP_COMPUTE_DEPTH_GRADX_BGR,
	KP_COMPUTE_DEPTH_GRADY_BGR,

	//KP_COMPUTE_BOX_AND_CLOUD_CLOUDS,

	KP_N_PROCESSES_SUPPORTED
};


shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>
	getKP(KinectProcessType kp);

class KinectProcessYUV2BGR :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->convertYUY2BGR();
	}

	void onStartup() {}
};

class KinectProcessComputeDepthL :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		//t->computeDepthLaplacian();
	}

	void onStartup() {}
};

class KinectProcessBodyCameraSP :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->computeBodyCameraSpacePts();
	}

	void onStartup() {}
};

class KinectProcessBodyColorSP :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->computeBodyColorSpacePts();
	}

	void onStartup() {}
};

class KinectProcessBodyDepthSP :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->computeBodyDepthSpacePts();
	}

	void onStartup() {}
};

class KinectProcessBodyOnHD :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->renderBodyOnHDBGRImage();
	}

	void onStartup() {}
};

class KinectProcessBodyOnDepth :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->renderBodyOnDepthBGRImage();
	}

	void onStartup() {}
};

class KinectProcessDepthCameraSP :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->computeDepthCameraSpacePts();
	}

	void onStartup() {}
};

class KinectProcessDepthColorSP :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->computeDepthColorSpacePts();
	}

	void onStartup() {}
};

class KinectProcessRegistration :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->computePtRegistration();
	}

	void onStartup() {}
};

class KinectProcessComputeDepth32FC1 :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		//t->computeDepth32FC1();
	}

	void onStartup() {}
};

class KinectProcessComputeDepth32FC1Blur :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		//t->computeDepth32FC1Blur();
	}

	void onStartup() {}
};

class KinectProcessComputeDepthGradX :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		//t->computeDepthGradX();
	}

	void onStartup() {}
};

class KinectProcessComputeDepthGradY :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		//t->computeDepthGradY();
	}

	void onStartup() {}
};

class KinectProcessComputeDepthGradXBGR :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		//t->computeDepthGradXBGR();
	}

	void onStartup() {}
};

class KinectProcessComputeDepthGradYBGR :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		//t->computeDepthGradYBGR();
	}

	void onStartup() {}
};

/*
class KinectProcessComputeBoxAndCloudClouds :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t) {
		t->computeBoxAndCloudClouds();
	}
};
*/

#endif