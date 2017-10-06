#ifndef F4_VECT_PT_3D_COL_H
#define F4_VECT_PT_3D_COL_H

#include "Pt3DCollection.h"
#include "TypeBroadcaster.h"

#include <util/mirrored_memory.h>

#include <opencv/cv.h>

#include <fstream>

class CameraModel;

class F4VectPt3DCol :
	public Pt3DCollection
	, public TypeBroadcaster<Pt3DCollection *> {
public:
	F4VectPt3DCol(CameraModel &cm);
	~F4VectPt3DCol();

	void update(cv::Mat &depthRGB
		, dart::MirroredVector<float4> &vertMap);

	//Pt3DCollection
	int getNPts();
	CameraSpacePoint *getCameraPt(int index);
	CameraSpacePoint *getCameraPts();
	unsigned char *getRGB();

protected:
	int _nPts;
	CameraSpacePoint *_cameraSpacePoints;
	cv::Mat _depthRGB;

	//ofstream _f;
};

#endif
