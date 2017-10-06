#ifndef ARRAY_PT_3D_COLLECTION_H
#define ARRAY_PT_3D_COLLECTION_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#include <registration.h>
#include <pthread.h>
#include <semaphore.h>
#endif

#include "FrameDesc.h"
#include "Pt3DCollection.h"

#include <opencv/cv.hpp>

//struct Point3DRGB;

class ArrayPt3DCollection : public Pt3DCollection {
public:
	ArrayPt3DCollection(
		int maxPts
		, libfreenect2::Registration &reg
		, FrameDesc &depthFD
		, cv::Mat &depthRGB
		, libfreenect2::Frame &depthUndistF);
	~ArrayPt3DCollection();

	void computeDepthCameraSpacePts();

	//Pt3DCollection
	int getNPts();
	int getMaxPts();

	CameraSpacePoint *getCameraPt(int index);
	CameraSpacePoint *getCameraPts();
	void setCameraPt(int index, CameraSpacePoint setVal);
	unsigned char *getRGB();

	cv::Mat &getBGRImage();

	//void copyIntoCollection(Point3DRGB *p);
	void clear();

protected:
	int _maxPts, _nPts;

	#ifdef _WIN32
	ICoordinateMapper &_cm;
	#elif __linux__
	libfreenect2::Registration &_reg;
	#endif

	FrameDesc &_depthFD;

	CameraSpacePoint *_cameraSpacePoints;
	//unsigned char *_bgr;

	cv::Mat &_depthRGB;
	libfreenect2::Frame &_depthUndistF;
};

#endif
