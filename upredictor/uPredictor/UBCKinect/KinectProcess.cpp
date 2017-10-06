#include "KinectProcess.h"

shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>
	getKP(KinectProcessType kp) {
	TypeRecipient<SimplePool<KinectFrame>::PooledPtr> *retVal = NULL;
	switch (kp) {
		case KP_CONVERT_YUV_2_BGR:
			retVal = new KinectProcessYUV2BGR();
			break;
		case KP_CONVERT_DEPTH_2_BGR:
			abort();
			break;
		case KP_COMPUTE_DEPTH_L:
			retVal = new KinectProcessComputeDepthL();
			break;
		case KP_CONVERT_DEPTH_L_2_BGR:
			abort();
			break;
		case KP_COMPUTE_BODY_CAMERA_SPACE_PTS:
			retVal = new KinectProcessBodyCameraSP();
			break;
		case KP_COMPUTE_BODY_COLOR_SPACE_PTS:
			retVal = new KinectProcessBodyColorSP();
			break;
		case KP_COMPUTE_BODY_DEPTH_SPACE_PTS:
			retVal = new KinectProcessBodyDepthSP();
			break;
		case KP_RENDER_BODY_ON_HD_BGR_IMAGE:
			retVal = new KinectProcessBodyOnHD();
			break;
		case KP_RENDER_BODY_ON_DEPTH_BGR_IMAGE:
			retVal = new KinectProcessBodyOnDepth();
			break;
		case KP_COMPUTE_DEPTH_CAMERA_SPACE_PTS:
			retVal = new KinectProcessDepthCameraSP();
			break;
		case KP_COMPUTE_DEPTH_COLOR_SPACE_PTS:
			retVal = new KinectProcessDepthColorSP();
			break;
		case KP_COMPUTE_PT_REGISTRATION:
			retVal = new KinectProcessRegistration();
			break;

		case KP_COMPUTE_DEPTH_32_FC1:
			retVal = new KinectProcessComputeDepth32FC1();
			break;
		case KP_COMPUTE_DEPTH_32_FC1_BLUR:
			retVal = new KinectProcessComputeDepth32FC1Blur();
			break;
		case KP_COMPUTE_DEPTH_32_FC1_GRADX:
			retVal = new KinectProcessComputeDepthGradX();
			break;
		case KP_COMPUTE_DEPTH_32_FC1_GRADY:
			retVal = new KinectProcessComputeDepthGradY();
			break;

		case KP_COMPUTE_DEPTH_GRADX_BGR:
			retVal = new KinectProcessComputeDepthGradXBGR();
			break;
		case KP_COMPUTE_DEPTH_GRADY_BGR:
			retVal = new KinectProcessComputeDepthGradYBGR();
			break;
		//case KP_COMPUTE_BOX_AND_CLOUD_CLOUDS:
		//	retVal = new KinectProcessComputeBoxAndCloudClouds();
		//	break;
	}
	return shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(retVal);
}