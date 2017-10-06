#ifndef KINECT_BODY_DECOMPRESS_H
#define KINECT_BODY_DECOMPRESS_H

#include "FileIndex.h"
#include "IBodyAttrDecompress.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"

//#include <lz4frame_static.h>

#include <string>

using namespace std;

struct FrameDesc;

class KinectBodyDecompress {
public:
	KinectBodyDecompress();
	KinectBodyDecompress(wstring fileName, int nBodies);
	~KinectBodyDecompress();

	bool open(wstring fileName, int nBodies);
	void close();

	void fillInFrame(SimplePool<KinectFrame>::PooledPtr t, long index);

	long getNFrames();

protected:
	IBodyAttrDecompress _comp;

	FileIndex *_fi;
	size_t _maxBufSize;
	char *_buf;
};

#endif