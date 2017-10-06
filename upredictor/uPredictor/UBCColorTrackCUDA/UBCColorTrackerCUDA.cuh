/*
Basic premise of the detector:
	Pick margins between color channels to track primary colored objects
*/

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#endif

#include "TrackerCUDAStructs.h"

void setupCUDA();

int setDevice();

CUDATracker setupCUDATracker
	(struct MarginalTrackerParams *marginalTrackerParams, int stream);

//typedef CUDATracker(CALLBACK* setupCUDATrackerType)
//	(struct MarginalTrackerParams *marginalTrackerParams, int stream);

CUDAComputeCloudNormals setupCloudNormalComp(int dimX, int dimY, int stream);

//typedef CUDAComputeCloudNormals(CALLBACK* setupCloudNormalCompType)
//	(int dimX, int dimY, int stream);

//inputImage - 24bit BGR image
//outputImage - 8bit 1C image containing segments
//marginalTrackerParams - MarginalTrackerParams
int doMarginalSegmentation(
		struct CUDATracker *ct
		, unsigned char *inputImage
		, unsigned char *outputImage
		, int *outputSegments);
	
void computeCloudNormals(
		struct CUDAComputeCloudNormals *ct,
		CameraSpacePoint *camPts
		, float *outVectsX, float *outVectsY
		, float *outNormsX, float *outNormsY
		, float *outSinesX, float *outSinesY
		, float *outCosinesX, float *outCosinesY);

CUDAComputeFloatToImage setupCUDAComputeFloatImage(int nPix, int nChans);

void computeFloatImage(float *inFloat, char *outImg, CUDAComputeFloatToImage *cccn);

CUDASphereDetector setupCUDAGridFilter(GridParams *gp);

void resizeGrid(
	float minX3D, float maxX3D,
	float minY3D, float maxY3D,
	float minZ3D, float maxZ3D,
	CUDASphereDetector *csd);

void computeCosts(
	CameraSpacePoint *hostPts
	, int *hostInputSegments
	, int segment
	, CUDASphereDetector *csd
	);

