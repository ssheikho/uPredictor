#ifndef MODTOOBS_H
#define MODTOOBS_H

#include <vector_types.h>

#include "grid_3d.h"
#include "SE3.h"
#include "UBCDARTMirroredModel.h"
#include "dart_types.h"

namespace dart {

	float errorModToObs(const float4 * dLabeledPredictedVertMap,
		const int width,
		const int height,
		const Grid3D<float> * dObsSdf);

	void normEqnsModToObs(const int dimensions,
		const float4 * dLabeledPredictedVertMap,
		const int width,
		const int height,
		const UBCDARTMirroredModel & model,
		const SE3 T_gc,
		float * dResult,
		int * numPredictions = 0,
		int * debugDataAssociation = 0,
		float * debugError = 0,
		float4 * debugNorm = 0);

	void normEqnsModToObsReduced(const int dims,
		const int reductionDims,
		const float * d_dtheta_dalpha,
		const float4 * dLabeledPredictedVertMap,
		const int width,
		const int height,
		const UBCDARTMirroredModel & model,
		float * dResult,
		int * numPredictions,
		int * debugDataAssociation = 0,
		float * debugError = 0,
		float4 * debugNorm = 0);

	void normEqnsModToObsParamMap(const int dims,
		const int reductionDims,
		const int * dMapping,
		const float4 * dLabeledPredictedVertMap,
		const int width,
		const int height,
		const UBCDARTMirroredModel & model,
		float * dResult,
		int * numPredictions,
		int * debugDataAssociation = 0,
		float * debugError = 0,
		float4 * debugNorm = 0);

	void normEqnsModToObsTruncated(const int dimensions,
		const float4 * dLabeledPredictedVertMap,
		const int width,
		const int height,
		const UBCDARTMirroredModel & model,
		const float truncationDistance,
		float * dResult,
		int * numPredictions = 0,
		int * debugDataAssociation = 0,
		float * debugError = 0,
		float4 * debugNorm = 0);

	void splatObsSdfZeros(const float4 * dObsVertMap,
		const int width,
		const int height,
		const SE3 & T_cm,
		const Grid3D<float> * dObsSdf,
		const uint3 sdfDim,
		const float focalLength);

	void computeTruncatedObsSdf(const float4 * dObsVertMap,
		const int width,
		const int height,
		const SE3 & T_mc,
		const Grid3D<float> * dObsSdf,
		const uint3 sdfDim,
		const float truncationDist);

	void cullUnobservable_(float4 * predVertMap,
		const int predWidth,
		const int predHeight,
		const float4 * obsVertMap,
		const int obsWidth,
		const int obsHeight,
		const cudaStream_t stream = 0);


}

#endif // MODTOOBS_H
