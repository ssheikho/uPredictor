#ifndef KINECT_DEPTH_COMPRESS_H
#define KINECT_DEPTH_COMPRESS_H

#include "FileIndex.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

#include <lz4frame_static.h>

#include <string>

using namespace std;

struct FrameDesc;

class KinectDepthCompress :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	KinectDepthCompress();
	#ifdef _WIN32
	KinectDepthCompress(wstring fileName, FrameDesc &fd);
	#elif __linux__
	KinectDepthCompress(string fileName, FrameDesc &fd);
	#endif
	~KinectDepthCompress();

	#ifdef _WIN32
	bool open(wstring fileName, FrameDesc &fd);
	#elif __linux__
	bool open(string fileName, FrameDesc &fd);
	#endif
	void close();

	//KinectImageFrameRecipient
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	FileIndex *_fi;

	int _imgSize, _maxSizeComp;
	char *_buf;
	LZ4F_compressionContext_t _cCtx;
};

#endif
