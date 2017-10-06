#ifndef KINECT_VIDEO_DECOMPRESS_H
#define KINECT_VIDEO_DECOMPRESS_H

#ifdef _WIN32
#define NOMINMAX
#endif

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"

#include <opencv2/opencv.hpp>

#include <string>

using namespace std;

struct FrameDesc;

class KinectVideoDecompress {
public:
	KinectVideoDecompress();
	#ifdef _WIN32	
	KinectVideoDecompress(wstring fileName, FrameDesc &fd);
	#elif __linux__
	KinectVideoDecompress(string fileName, FrameDesc &fd);
	#endif
	~KinectVideoDecompress();

	#ifdef _WIN32
	bool open(wstring fileName, FrameDesc &fd);
	#elif __linux__
	bool open(string fileName, FrameDesc &fd);
	#endif
	void close();

	void fillInFrame(SimplePool<KinectFrame>::PooledPtr t, long index);

	long nFrames();
	long curFrame();

protected:
	cv::VideoCapture *_vc;
	long _nFrames, _curFrame;
	bool _isOpen;
};

#endif
