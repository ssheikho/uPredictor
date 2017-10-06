#ifndef SPHERE_DETECTOR_INFO_H
#define SPHERE_DETECTOR_INFO_H

#include "FrameDesc.h"
#include "ThreeDBB.h"
#include "../UBCColorTrackCUDA/TrackerCUDAStructs.h"

#include <opencv/cv.h>

class SphereDetectorInfo {
public:
	SphereDetectorInfo(FrameDesc &depthFD);

	~SphereDetectorInfo();

	void update(GridParams gp, CameraSpacePoint *pts3D);

	GridParams &getGP();
	CameraSpacePoint *getCenters();

	//Detector image
	cv::Mat _depthSegImg;

	//Detector map
	int *_depthSegMap;

	//Detector BB
	ThreeDBB _threeDBB;

protected:
	//Detector sphere grids
	GridParams _gp;
	CameraSpacePoint *_pts3D;

	//Detected spheres
};

#endif
