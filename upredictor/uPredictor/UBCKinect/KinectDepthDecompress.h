#ifndef KINECT_DEPTH_DECOMPRESS_H
#define KINECT_DEPTH_DECOMPRESS_H

#ifdef _WIN32
#include <WinSock2.h>
#include "Windows.h"
#endif

#include "FileIndex.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"

#include <lz4frame_static.h>

#include <string>

using namespace std;

class KinectImageFrame;
struct FrameDesc;
struct RefCountedPool;

class KinectDepthDecompress {
public:
	KinectDepthDecompress();
	#ifdef _WIN32
	KinectDepthDecompress(wstring fileName, FrameDesc &fd);
	#elif __linux__
	KinectDepthDecompress(string fileName, FrameDesc &fd);
	#endif
	~KinectDepthDecompress();

	#ifdef _WIN32
	bool open(wstring fileName, FrameDesc &fd);
	#elif __linux__
	bool open(string fileName, FrameDesc &fd);
	#endif
	void close();

	void fillInFrame(SimplePool<KinectFrame>::PooledPtr t, long index);

	long getNFrames();

protected:
	FileIndex *_fi;
	int _imgSize, _maxSizeComp;;
	char *_buf;
	LZ4F_decompressionContext_t _dCtx;
};

#endif
