#ifndef UBC_COLOR_TRACKER_CUDA_H
#define UBC_COLOR_TRACKER_CUDA_H

#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>

#include "TrackerCUDAStructs.h"
#include "cuda_runtime.h"

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
	// used by C++ source code
#endif

	/*
void setupCUDA();
int setDevice();

CUDATracker setupCUDATracker(
	struct MarginalTrackerParams *marginalTrackerParams, int stream);

CUDAComputeCloudNormals setupCloudNormalComp(int dimX, int dimY, int stream);


//inputImage - 24bit BGR image
//outputImage - 8bit 1C image containing segments
//marginalTrackerParams - MarginalTrackerParams

int doMarginalSegmentationSimple(
	struct CUDATracker *ct
	, unsigned char *inputImage
	, unsigned char *outputImage);

void computeCloudNormals(
	struct CUDAComputeCloudNormals *ct
	, CameraSpacePoint *camPts
	, float *outVectsX, float *outVectsY
	, float *outNormsX, float *outNormsY
	, float *outSinesX, float *outSinesY
	, float *outCosinesX, float *outCosinesY);
*/

#ifdef __cplusplus
}
#endif

#endif