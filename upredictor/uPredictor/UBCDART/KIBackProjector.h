#ifndef KI_BACK_PROJECTOR_H
#define KI_BACK_PROJECTOR_H

#include "optimization/optimization.h"
#include "optimization/optimizer.h"
#include "optimization/prediction_renderer.h"
#include "optimization/priors.h"
#include "depth_sources/depth_source.h"
#include "model/mirrored_model.h"
#include "pose/pose.h"

class CameraModel;

namespace dart {
class KIBackProjector {
public:
	KIBackProjector(CameraModel &cm);
	~KIBackProjector();

	 void backProjectDepthMap(const float *depthMap, float4 *vertMap
		, int *segMap);

protected:
	CameraModel &_cm;
};
}

#endif
