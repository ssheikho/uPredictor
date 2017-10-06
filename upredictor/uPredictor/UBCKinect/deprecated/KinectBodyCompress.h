#ifndef KINECT_BODY_COMPRESS_H
#define KINECT_BODY_COMPRESS_H

#include "FileIndex.h"
#include "IBodyAttrCompress.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

//#include <lz4frame_static.h>

#include <string>

using namespace std;

struct FrameDesc;

class KinectBodyCompress :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	KinectBodyCompress();
	KinectBodyCompress(wstring fileName, int nBodies);
	~KinectBodyCompress();

	bool open(wstring fileName, int nBodies);
	void close();

	//KinectImageFrameRecipient
	void processType(SimplePool<KinectFrame>::PooledPtr t);

protected:
	IBodyAttrCompress _comp;

	FileIndex *_fi;
	size_t _curBufSize, _maxBufSize;
	char *_buf;
};

#endif