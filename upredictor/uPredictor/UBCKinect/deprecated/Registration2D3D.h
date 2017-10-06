#ifndef REGISTRATION_2D_3D_H
#define REGISTRATION_2D_3D_H

//#include "KinectFrame.h"

#include "FrameDesc.h"
#include "Point3DRGB.h"

#include <opencv/cv.hpp>

#include <Eigen/Core>

#include <vector>

//using namespace Eigen;
//using namespace std;

struct FrameDesc;
class ArrayPt3DCollection;
class KinectFrame;

class Registration2D3D {
public:
	Registration2D3D(
		FrameDesc &bgraFD
		, FrameDesc &depthFD
		, ArrayPt3DCollection *pts
		, int channel = 0
		);
	~Registration2D3D();
	
	FrameDesc &getColorFrameDesc();
	FrameDesc &getDepthFrameDesc();
	FrameDesc &getColorDepthFrameDesc();

	//KinectImageFrameRecipient
	void processKinectFrame(KinectFrame *kf);

protected:
	void zeroOut();
	long liesInColorGrid(int x, int y);

	int ptGridIndex(int x, int y);
	bool inBounds(int loX, int loY, int hiX, int hiY);
	FrameDesc &_yuyFD, &_depthFD, _colorDepthMap;
	ArrayPt3DCollection *_pts;
	int _channel;
	int _nCameraPts, _nColorPts;

	//Point3DRGB *_cameraPts;
	float *_colorPtGridZ;
};

#endif
