#ifndef TRACKER_CUDA_STRUCTS_H
#define TRACKER_CUDA_STRUCTS_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>
#include <Windows.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#endif

#include "../UBCSimpleGeometry/UBCSimpleGeometry.h"

struct GridParams {
	int _gridDim, _nGridCells, _nPts;
	float _r, _d
		//, _xMinSpan, _yMinSpan, _zMinSpan
		, _xSliceWidth, _ySliceWidth, _zSliceWidth
		, _xFirstCenter, _yFirstCenter, _zFirstCenter;
};

struct CUDASphereDetector {
	CameraSpacePoint *_hostCenters, *_devCenters, *_devPts;
	float *_hostCosts, *_devCosts;
	int *_hostSphereAssignments, *_devSphereAssignments,
		*_devInputSegments;
	GridParams *_hostGridParams, *_devGridParams;
	int _blockR, _gridR, _blockCC, _gridCC;
};

struct MarginalTrackerParams {
	long
		_nchans			/*Number of color channels*/
		, _npix			/*Number of pixels*/
		, _sizeII		/*Number of pixels * number of channels*/
		, _mostlyChan	/*Object is "mostly" this color*/
		, _fromChanA	/*Color to be subtracted A*/
		, _fromChanB	/*Color to be subtracted B*/

		/*How much more blue should it be than red? Green?*/
		, _marginA		/*_mostlyChan - fromChanA margin*/
		, _marginB		/*_mostlyChan - fromChanB margin*/
		, _indicColorB
		, _indicColorG
		, _indicColorR
		;
};

struct CUDATracker {
	unsigned char *_devInputImage, *_devOutputImage;
	MarginalTrackerParams *_marginalTrackerParams
		, *_devMarginalTrackerParams;
	int _blockSize, _gridSize, _stream, *_devOutputSegments;
};

struct CUDAComputeCloudNormals {
	CameraSpacePoint *_devCamPts;
	float
		*_devOutVectsX, *_devOutVectsY
		, *_devOutNormsX, *_devOutNormsY
		, *_devSineX, *_devSineY
		, *_devCosineX, *_devCosineY;
	long _pts, _dimX, _dimY;
	int
		_blockSizeN, _gridSizeN
		, _blockSizeS, _gridSizeS
		, _stream;
};

struct CUDAComputeFloatToImage {
	float *_devFloat;
	char *_devImage;
	int _nChans, _nPix;
	int _blockSize, _gridSize, _stream;
};


#endif
