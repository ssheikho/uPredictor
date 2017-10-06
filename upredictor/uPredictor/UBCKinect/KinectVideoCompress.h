#ifndef KINECT_VIDEO_COMPRESS_H
#define KINECT_VIDEO_COMPRESS_H

#ifdef _WIN32
#define NOMINMAX
#elif __linux__
#include <pthread.h>
#endif

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

#include <opencv2/opencv.hpp>

#include <string>

using namespace std;

struct FrameDesc;

class KinectVideoCompress :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	KinectVideoCompress();
	#ifdef _WIN32
	KinectVideoCompress(wstring fileName, FrameDesc &fd);
	#elif __linux__
	KinectVideoCompress(string fileName, FrameDesc &fd);
	#endif
	~KinectVideoCompress();

	#ifdef _WIN32
	bool open(wstring fileName, FrameDesc &fd);
	#elif __linux__
	bool open(string fileName, FrameDesc &fd);
	#endif
	void close();

	void processType(SimplePool<KinectFrame>::PooledPtr t);

protected:
	cv::VideoWriter *_vw;
	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif
};

#endif
