#define _EXPORTING
#include "UBCColorTrackerCUDA.cuh"
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <cstring>
#include <vector>

__global__ void addKernel(int *c, const int *a, const int *b)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

__global__ void cloudNormalKernel(
	CameraSpacePoint *camPts
	, float *outVectsX, float *outVectsY
	, float *outNormsX, float *outNormsY
	, int dimX, int dimY) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int maxIdx = dimX * dimY;
	int nextX = idx + 1;
	int nextY = idx + dimX;

	int idx3 = idx * 3;

	if (nextX % dimX != 0) {
		float x = outVectsX[idx3] = (camPts[nextX].X - camPts[idx].X);
		float y = outVectsX[idx3 + 1] = (camPts[nextX].Y - camPts[idx].Y);
		float z = outVectsX[idx3 + 2] = (camPts[nextX].Z - camPts[idx].Z);

		outNormsX[idx] = sqrt(x * x + y * y + z * z);

		outVectsX[idx3] /= outNormsX[idx];
		outVectsX[idx3 + 1] /= outNormsX[idx];
		outVectsX[idx3 + 2] /= outNormsX[idx];
	}

	if (nextY < maxIdx) {
		float x = outVectsY[idx3] = (camPts[nextY].X - camPts[idx].X);
		float y = outVectsY[idx3 + 1] = (camPts[nextY].Y - camPts[idx].Y);
		float z = outVectsY[idx3 + 2] = (camPts[nextY].Z - camPts[idx].Z);

		outNormsY[idx] = sqrt(x * x + y * y + z * z);

		outVectsY[idx3] /= outNormsY[idx];
		outVectsY[idx3 + 1] /= outNormsY[idx];
		outVectsY[idx3 + 2] /= outNormsY[idx];
	}
}

void setupCUDA() {}

int setDevice() {
	cudaError_t cudaStatus = cudaSetDevice(0);
	return 0;
}

__global__ void marginalSegmentationKernel(
	unsigned char *inputImage
	, unsigned char *outputImage
	, int *outputSegments
	, MarginalTrackerParams *params) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int idxThreeX = 3 * idx;
	if (
		((inputImage[idxThreeX + params->_mostlyChan] -
		inputImage[idxThreeX + params->_fromChanA]) > params->_marginA) &&
		((inputImage[idxThreeX + params->_mostlyChan] -
		inputImage[idxThreeX + params->_fromChanB]) > params->_marginB)
		) {
		outputImage[idxThreeX] = params->_indicColorB;
		outputImage[idxThreeX + 1] = params->_indicColorG;
		outputImage[idxThreeX + 2] = params->_indicColorR;
		outputSegments[idx] = 20;
	}
	else {
		outputImage[idxThreeX] = inputImage[idxThreeX];
		outputImage[idxThreeX + 1] = inputImage[idxThreeX + 1];
		outputImage[idxThreeX + 2] = inputImage[idxThreeX + 2];
		outputSegments[idx] = -1;
	}
}

CUDATracker setupCUDATracker(
	struct MarginalTrackerParams *marginalTrackerParams, int stream) {
	cudaError_t cudaStatus;

	CUDATracker tracker;

	cudaStatus = cudaMalloc((void**)&tracker._devInputImage
		, marginalTrackerParams->_sizeII);
	cudaStatus = cudaMalloc((void**)&tracker._devOutputImage
		, marginalTrackerParams->_sizeII);
	cudaStatus = cudaMalloc((void**)&tracker._devOutputSegments
		, marginalTrackerParams->_npix * sizeof(int));
	cudaStatus = cudaMalloc((void**)&tracker._devMarginalTrackerParams
		, sizeof(MarginalTrackerParams));

	cudaStatus = cudaMemcpy(tracker._devMarginalTrackerParams, marginalTrackerParams
		, sizeof(MarginalTrackerParams), cudaMemcpyHostToDevice);

	tracker._marginalTrackerParams = marginalTrackerParams;

	int minGridSize;

	cudaOccupancyMaxPotentialBlockSize(&minGridSize,
		&tracker._blockSize,
		marginalSegmentationKernel, 0, 0);

	tracker._gridSize =
		(marginalTrackerParams->_npix + tracker._blockSize - 1)
		/ tracker._blockSize;
	
	return tracker;
}

int doMarginalSegmentation(
	struct CUDATracker *ct
	, unsigned char *inputImage
	, unsigned char *outputImage
	, int *outputSegments) {
	cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(ct->_devInputImage, inputImage
		, ct->_marginalTrackerParams->_sizeII, cudaMemcpyHostToDevice);

	cudaStatus =
		cudaMemcpy(ct->_devMarginalTrackerParams, ct->_marginalTrackerParams
		, sizeof(MarginalTrackerParams), cudaMemcpyHostToDevice);

	marginalSegmentationKernel << <ct->_gridSize, ct->_blockSize >> >
		(ct->_devInputImage, ct->_devOutputImage, ct->_devOutputSegments
		, ct->_devMarginalTrackerParams);

	cudaStatus = cudaDeviceSynchronize();

	cudaStatus = cudaMemcpy(outputImage, ct->_devOutputImage
		, ct->_marginalTrackerParams->_sizeII, cudaMemcpyDeviceToHost);

	cudaStatus = cudaMemcpy(outputSegments, ct->_devOutputSegments
		, ct->_marginalTrackerParams->_npix * sizeof(int)
		, cudaMemcpyDeviceToHost);

	return 0;
}

__global__ void cloudSineKernel(
	CameraSpacePoint *camPts
	, float *inVectsX, float *inVectsY
	, float *outSinesX, float *outSinesY
	, float *outCosinesX, float *outCosinesY
	, int dimX, int dimY) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int maxIdx = dimX * dimY;
	int nextX = idx + 1;
	int nextY = idx + dimX;

	int idx3 = idx * 3;

	if (nextX < maxIdx) {
		if ((nextX % dimX) > 0) {
			int nextX3 = nextX * 3;

			float aX = inVectsX[idx3];
			float aY = inVectsX[idx3 + 1];
			float aZ = inVectsX[idx3 + 2];

			float bX = inVectsX[nextX3];
			float bY = inVectsX[nextX3 + 1];
			float bZ = inVectsX[nextX3 + 2];

			float cX = aZ * bY - aY * bZ;
			float cY = aX * bZ - aZ * bX;
			float cZ = aY * bX - aX * bY;

			outSinesX[idx] = aX;// *bX + aY * bY + aZ * bZ;
			outCosinesX[idx] = sqrt(cX + cY + cZ);

		}
		else {
			outSinesX[idx] = 0;
			outCosinesX[idx] = 0;
		}

		if (nextY < maxIdx) {
			int nextY3 = nextY * 3;

			float aX = inVectsY[idx3];
			float aY = inVectsY[idx3 + 1];
			float aZ = inVectsY[idx3 + 2];

			float bX = inVectsY[nextY3];
			float bY = inVectsY[nextY3 + 1];
			float bZ = inVectsY[nextY3 + 2];

			float cX = aZ * bY - aY * bZ;
			float cY = aX * bZ - aZ * bX;
			float cZ = aY * bX - aX * bY;

			outSinesY[idx] = aX;// *bX + aY * bY + aZ * bZ;
			outCosinesY[idx] = sqrt(cX + cY + cZ);
		}
		else {
			outSinesY[idx] = 0;
			outCosinesY[idx] = 0;
		}
	}
	else {
		outSinesX[idx] = 0;
		outSinesY[idx] = 0;
		outCosinesX[idx] = 0;
		outCosinesY[idx] = 0;
	}
}

CUDAComputeCloudNormals setupCloudNormalComp(int dimX, int dimY, int stream) {
	cudaError_t cudaStatus;
	CUDAComputeCloudNormals ccn;
	ccn._dimX = dimX;
	ccn._dimY = dimY;
	ccn._pts = dimX * dimY;

	cudaStatus = cudaMalloc((void**)&ccn._devCamPts, ccn._pts * sizeof(CameraSpacePoint));

	cudaStatus = cudaMalloc((void**)&ccn._devOutVectsX, ccn._pts * 3 * sizeof(float));
	cudaStatus = cudaMalloc((void**)&ccn._devOutVectsY, ccn._pts * 3 * sizeof(float));

	cudaStatus = cudaMalloc((void**)&ccn._devOutNormsX, ccn._pts * sizeof(float));
	cudaStatus = cudaMalloc((void**)&ccn._devOutNormsY, ccn._pts * sizeof(float));

	cudaStatus = cudaMalloc((void**)&ccn._devSineX, ccn._pts * sizeof(float));
	cudaStatus = cudaMalloc((void**)&ccn._devSineY, ccn._pts * sizeof(float));

	cudaStatus = cudaMalloc((void**)&ccn._devCosineX, ccn._pts * sizeof(float));
	cudaStatus = cudaMalloc((void**)&ccn._devCosineY, ccn._pts * sizeof(float));

	int minGridSize;

	cudaOccupancyMaxPotentialBlockSize(&minGridSize,
		&ccn._blockSizeN,
		cloudNormalKernel, 0, 0);

	ccn._gridSizeN = (ccn._pts + ccn._blockSizeN - 1) / ccn._blockSizeN;

	cudaOccupancyMaxPotentialBlockSize(&minGridSize,
		&ccn._blockSizeS,
		cloudSineKernel, 0, 0);

	ccn._gridSizeS = (ccn._pts + ccn._blockSizeS - 1) / ccn._blockSizeS;

	//cuCtxPopCurrent(&_contexts[ccn._stream]);

	//ReleaseMutex(_cudaMutex);

	return ccn;
}

void computeCloudNormals(
	struct CUDAComputeCloudNormals *ct
	, CameraSpacePoint *camPts
	, float *outVectsX, float *outVectsY
	, float *outNormsX, float *outNormsY
	, float *outSinesX, float *outSinesY
	, float *outCosinesX, float *outCosinesY) {
	cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(ct->_devCamPts, camPts
		, ct->_pts * sizeof(CameraSpacePoint), cudaMemcpyHostToDevice);
	
	//, 0, _streams[ct->_stream]
	cloudNormalKernel << <ct->_gridSizeN, ct->_blockSizeN >> > (
		ct->_devCamPts
		, ct->_devOutVectsX, ct->_devOutVectsY
		, ct->_devOutNormsX, ct->_devOutNormsY
		, ct->_dimX, ct->_dimY);

	cudaStatus = cudaDeviceSynchronize();

	//, 0, _streams[ct->_stream]
	cloudSineKernel << <ct->_gridSizeS, ct->_blockSizeS>> > (
		ct->_devCamPts
		, ct->_devOutVectsX, ct->_devOutVectsY
		, ct->_devSineX, ct->_devSineY
		, ct->_devCosineX, ct->_devCosineY
		, ct->_dimX, ct->_dimY);

	cudaStatus = cudaDeviceSynchronize();
	
	cudaStatus = cudaMemcpy(outVectsX, ct->_devOutVectsX
		, ct->_pts * 3 * sizeof(float), cudaMemcpyDeviceToHost);
	cudaStatus = cudaMemcpy(outVectsY, ct->_devOutVectsY
		, ct->_pts * 3 * sizeof(float), cudaMemcpyDeviceToHost);

	cudaStatus = cudaMemcpy(outNormsX, ct->_devOutNormsX
		, ct->_pts * sizeof(float), cudaMemcpyDeviceToHost);
	cudaStatus = cudaMemcpy(outNormsY, ct->_devOutNormsY
		, ct->_pts * sizeof(float), cudaMemcpyDeviceToHost);

	cudaStatus = cudaMemcpy(outSinesX, ct->_devSineX
		, ct->_pts * sizeof(float), cudaMemcpyDeviceToHost);
	cudaStatus = cudaMemcpy(outSinesY, ct->_devSineY
		, ct->_pts * sizeof(float), cudaMemcpyDeviceToHost);

	cudaStatus = cudaMemcpy(outCosinesX, ct->_devCosineX
		, ct->_pts * sizeof(float), cudaMemcpyDeviceToHost);
	cudaStatus = cudaMemcpy(outCosinesY, ct->_devCosineY
		, ct->_pts * sizeof(float), cudaMemcpyDeviceToHost);

	//cuCtxPopCurrent(&_contexts[ct->_stream]);

	//ReleaseMutex(_cudaMutex);
}

__global__ void floatImageKernel(float *devFloat, char *devImage, int nChans
	, int nPix) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int idx3 = idx * 3;
	char v = ceil(255.0 * devFloat[idx]);
	devImage[idx3] = v;
	devImage[idx3 + 1] = v;
	devImage[idx3 + 2] = v;
}

CUDAComputeFloatToImage setupCUDAComputeFloatImage(int nPix, int nChans) {
	//WaitForSingleObject(_cudaMutex, INFINITE);

	cudaError_t cudaStatus;

	CUDAComputeFloatToImage trac;
	trac._nChans = nChans;
	trac._nPix = nPix;

	//Allocate buffers on GPU for parameters
	cudaStatus = cudaMalloc((void**)&trac._devFloat, nPix * sizeof(float));
	cudaStatus = cudaMalloc((void**)&trac._devImage, nPix * 3 * sizeof(char));

	int minGridSize;

	cudaOccupancyMaxPotentialBlockSize(&minGridSize,
		&trac._blockSize,
		floatImageKernel, 0, 0);

	trac._gridSize = (nPix + trac._blockSize - 1) / trac._blockSize;

	//cudaFree(trac._devFloat);
	//cudaFree(trac._devImage);

	//ReleaseMutex(_cudaMutex);

	return trac;
}

void computeFloatImage(float *inFloat, char *outImg, CUDAComputeFloatToImage *cccn) {
	//WaitForSingleObject(_cudaMutex, INFINITE);

	cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(cccn->_devFloat, inFloat
		, cccn->_nPix * sizeof(float), cudaMemcpyHostToDevice);

	floatImageKernel << <cccn->_gridSize, cccn->_blockSize >> >(
		cccn->_devFloat, cccn->_devImage, cccn->_nChans, cccn->_nPix);

	cudaStatus = cudaDeviceSynchronize();

	cudaStatus = cudaMemcpy(outImg, cccn->_devImage
		, cccn->_nPix * 3 * sizeof(char), cudaMemcpyDeviceToHost);

	//for (int i = 0; i < 10000; i++) outImg[i] = 200;

	//ReleaseMutex(_cudaMutex);
}