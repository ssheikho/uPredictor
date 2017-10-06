#define _EXPORTING
#include "UBCColorTrackerCUDA.cuh"
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <cstring>
#include <vector>

__global__ void resizeGridKernel(
	CameraSpacePoint *centers
	, struct GridParams *gp
	) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if (idx < gp->_nGridCells) {
		int xPos = idx % gp->_gridDim;
		int idxModX = (idx - xPos) / gp->_gridDim;
		int yPos = idxModX % gp->_gridDim;
		int zPos = (idxModX - yPos) / gp->_gridDim;

		centers[idx].X = gp->_xFirstCenter +((double)xPos * gp->_xSliceWidth);
		centers[idx].Y = gp->_yFirstCenter +((double)yPos * gp->_ySliceWidth);
		centers[idx].Z = gp->_zFirstCenter +((double)zPos * gp->_zSliceWidth);
	}

}

__global__ void computeCostsKernel (
	CameraSpacePoint *centers
	, CameraSpacePoint *pts
	, int *inputSegments
	, int segment
	, float *costs
	, int *assignments
	, struct GridParams *gp
	) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if (idx < gp->_nPts) {
		if (inputSegments[idx] == segment) {
			int assignment = 0;
			float xx = centers[0].X - pts[idx].X;
			float yy = centers[0].Y - pts[idx].Y;
			float zz = centers[0].Z - pts[idx].Z;
			float cost = fabs(sqrt(xx + yy + zz) - gp->_r);
			for (int i = 1; i < gp->_nGridCells; i++) {
				xx = centers[i].X - pts[idx].X;
				yy = centers[i].Y - pts[idx].Y;
				zz = centers[i].Z - pts[idx].Z;
				float curcost = fabs(sqrt(xx + yy + zz) - gp->_r);
				if (curcost < cost) {
					cost = curcost;
					assignment = i;
				}
			}
			costs[idx] = cost;
			assignments[idx] = assignment;
		}
		else {
			costs[idx] = -1.0f;
			assignments[idx] = -1;
		}
	}
}

CUDASphereDetector setupCUDAGridFilter(GridParams *gp) {
	cudaError_t cudaStatus;

	CUDASphereDetector retVal;
	retVal._hostGridParams = gp;
	gp->_nGridCells = gp->_gridDim * gp->_gridDim * gp->_gridDim;

	retVal._hostCenters = new CameraSpacePoint[gp->_nGridCells];
	retVal._hostCosts = new float[gp->_nGridCells];
	retVal._hostSphereAssignments = new int[gp->_nPts];

	cudaStatus = cudaMalloc((void**)&retVal._devPts
		, gp->_nPts * sizeof(CameraSpacePoint));
	cudaStatus = cudaMalloc((void**)&retVal._devCenters
		, gp->_nGridCells * sizeof(CameraSpacePoint));
	cudaStatus = cudaMalloc((void**)&retVal._devCosts
		, gp->_nGridCells * sizeof(float));
	cudaStatus = cudaMalloc((void**)&retVal._devSphereAssignments
		, gp->_nPts * sizeof(int));
	cudaStatus = cudaMalloc((void**)&retVal._devInputSegments
		, gp->_nPts * sizeof(int));
	cudaStatus = cudaMalloc((void**)&retVal._devGridParams
		, sizeof(GridParams));

	int minGridSize;

	cudaOccupancyMaxPotentialBlockSize(&minGridSize, &retVal._blockR
		, resizeGridKernel, 0, 0);

	retVal._gridR = (gp->_nGridCells + retVal._blockR - 1) / retVal._blockR;
	
	cudaOccupancyMaxPotentialBlockSize(&minGridSize, &retVal._blockCC
		, computeCostsKernel, 0, 0);

	retVal._gridCC = (gp->_nPts + retVal._blockCC - 1) / retVal._blockCC;

	return retVal;
}

//Compute diameter of a sphere
//double d = 2.0 * csd->_r;
void resizeGrid(
	float minX3D, float maxX3D,
	float minY3D, float maxY3D,
	float minZ3D, float maxZ3D,
	CUDASphereDetector *csd) {
	cudaError_t cudaStatus;
	GridParams *hgp = csd->_hostGridParams;

	hgp->_d = 2.0 * hgp->_r;

	float xMaxSpan = (maxX3D + hgp->_d);
	float yMaxSpan = (maxY3D + hgp->_d);
	float zMaxSpan = (maxZ3D + hgp->_d);

	float xMinSpan = (minX3D - hgp->_d);
	float yMinSpan = (minY3D - hgp->_d);
	float zMinSpan = (minZ3D - hgp->_d);

	float xSpan = xMaxSpan - xMinSpan;
	float ySpan = yMaxSpan - yMinSpan;
	float zSpan = zMaxSpan - zMinSpan;

	hgp->_xSliceWidth = xSpan / (double)(hgp->_gridDim);
	hgp->_ySliceWidth = ySpan / (double)(hgp->_gridDim);
	hgp->_zSliceWidth = zSpan / (double)(hgp->_gridDim);

	hgp->_xFirstCenter = xMinSpan + hgp->_r;
	hgp->_yFirstCenter = yMinSpan + hgp->_r;
	hgp->_zFirstCenter = zMinSpan + hgp->_r;

	cudaStatus = cudaMemcpy(csd->_devGridParams, csd->_hostGridParams
		, sizeof(GridParams), cudaMemcpyHostToDevice);

	resizeGridKernel << <csd->_gridR, csd->_blockR >> >
		(csd->_devCenters, csd->_devGridParams);

	cudaStatus = cudaDeviceSynchronize();

	cudaStatus = cudaMemcpy(csd->_hostCenters, csd->_devCenters
		, hgp->_nGridCells
		* sizeof(CameraSpacePoint), cudaMemcpyDeviceToHost);
}

void computeCosts(
	CameraSpacePoint *hostPts
	, int *hostInputSegments
	, int segment
	, CUDASphereDetector *csd
	) {
	GridParams *hgp = csd->_hostGridParams;

	cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(csd->_devPts, hostPts
		, hgp->_nPts * sizeof(CameraSpacePoint), cudaMemcpyHostToDevice);
	cudaStatus = cudaMemcpy(csd->_devInputSegments, hostInputSegments
		, hgp->_nPts * sizeof(int), cudaMemcpyHostToDevice);

	computeCostsKernel << <csd->_gridCC, csd->_blockCC >> >
		(csd->_devCenters, csd->_devPts, csd->_devInputSegments, segment
			, csd->_devCosts, csd->_devSphereAssignments, csd->_devGridParams);
	cudaStatus = cudaDeviceSynchronize();

	cudaStatus = cudaMemcpy(csd->_hostCosts, csd->_devCosts
		, hgp->_nPts * sizeof(float), cudaMemcpyDeviceToHost);
	cudaStatus = cudaMemcpy(csd->_hostSphereAssignments, csd->_devSphereAssignments
		, hgp->_nPts * sizeof(int), cudaMemcpyDeviceToHost);

}