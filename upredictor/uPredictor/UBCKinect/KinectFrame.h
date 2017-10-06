#ifndef KINECT_FRAME_H
#define KINECT_FRAME_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "registration.h"
#endif

#include "ArrayPt3DCollection.h"
#include "BoxAndConstellation.h"
#include "ImageChannelProvider.h"
#include "SphereDetectorInfo.h"
#include "SimplePool.h"
#include "../UBCSimpleGeometry/UBCSimpleGeometry.h"
//#include "UBCSimpleGeometry.h"

#include <opencv/cv.h>

#include <map>
#include <set>
#include <vector>

//using namespace std;

class ProcessingParameters;
class TrackIDManager;
struct FrameDesc;

class KinectFrame :
	public ImageChannelProvider
{
public:
	enum KinectFrameImageSources {
		KF_SOURCE_HD_BGRA
		, KF_SOURCE_HD_RGBA
		, KF_SOURCE_HD_RGB
		, KF_SOURCE_DEPTH_BGRA
		, KF_SOURCE_DEPTH_RGBA
		, KF_SOURCE_DEPTH_RGB
		, KF_SOURCE_DEPTH_32FC1
		, KF_SOURCE_COUNT
	};

	enum KinectFrameHDBGRA {
		KF_HD_BGRA
		, KF_HD_BGRA_COUNT
	};

	enum KinectFrameHDRGBA {
		KF_HD_RGBA
		, KF_HD_RGBA_COUNT
	};

	enum KinectFrameHDRGB {
		KF_HD_RGB
		, KF_HD_RGB_COUNT
	};

	enum KinectFrameDepthBGRA {
		KF_DEPTH_COLOR_BGRA
		, KF_DEPTH_BGRA_COUNT
	};

	enum KinectFrameDepthRGBA {
		KF_DEPTH_COLOR_RGBA
		, KF_DEPTH_RGBA_COUNT
	};

	enum KinectFrameDepthRGB {
		KF_DEPTH_COLOR_RGB
		, KF_DEPTH_SEGS_RGB
		, KF_DEPTH_RGB_COUNT
	};
	
	
	enum KinectFrameDepth32FC1 {
		KF_DEPTH32FC1_COUNT
	};

	KinectFrame(
		FrameDesc &bgraFD
		, FrameDesc &depthFD
		, TrackIDManager &tidm
		, libfreenect2::Registration &frereg
		);
	~KinectFrame();

	void clear();

	void convertHDBGRAToRGBA();
	void convertHDBGRAToRGB();
	void convertRegBGRAToRGBA();
	void convertRegBGRAToRGB();

	void computeRegistration();
	void computeDepthCameraSpacePts();
	void undistortDepth();
	
	ArrayPt3DCollection &getRegisteredPts();

	//ImageChannelProvider
	cv::Mat &getImageChannel(size_t source, size_t which);

	//Tracked objects, the int is the tracker ID
	map<int, vector<SimplePool<BoxAndConstellation>::PooledPtr>> _boxes;

	//Generalize this to tracked "objects"
	map<int, vector<UBCSphere>> _spheres;

protected:
	libfreenect2::Registration &_frereg;

	cv::Mat
		*_hdBGRAImgs[KF_HD_BGRA_COUNT]
		, *_hdRGBAImgs[KF_HD_RGBA_COUNT]
		, *_hdRGBImgs[KF_HD_RGB_COUNT]
		, *_depthBGRAImgs[KF_DEPTH_BGRA_COUNT]
		, *_depthRGBAImgs[KF_DEPTH_RGBA_COUNT]
		, *_depthRGBImgs[KF_DEPTH_RGB_COUNT];

public:
	libfreenect2::Frame _depthF, _bgraF, _depthUndistF, _depthBGRAF;
	cv::Mat
		_bgra
		, _rgba
		, _rgb
		, _depthBGRA
		, _depthRGBA
		, _depthRGB
		;

	SphereDetectorInfo _sdi;

	uint32_t _timeStamp;
	long _kinectIndex, _frameNo;

	ArrayPt3DCollection _pts;

	cv::Scalar _c;
};

#endif
