#include "KIBackProjector.h"
#include "CameraModel.h"

void KIDepthToVertices(const float *depthIn, float4 *vertOut, int *segMap
	, const int width, const int height, const float2 pp, const float2 fl);

namespace dart {
KIBackProjector::KIBackProjector(CameraModel &cm) : _cm(cm) {}

KIBackProjector::~KIBackProjector() {}

void KIBackProjector::backProjectDepthMap(
	const float *depthMap, float4 *vertMap, int *segMap) {
	KIDepthToVertices(depthMap, vertMap, segMap
		, _cm._width, _cm._height
		, make_float2(_cm._uZero, _cm._vZero)
		, make_float2(_cm._alpha, _cm._beta));
}

}
