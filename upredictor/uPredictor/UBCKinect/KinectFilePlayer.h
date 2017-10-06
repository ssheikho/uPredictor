#ifndef KINECT_FILE_PLAYER_H
#define KINECT_FILE_PLAYER_H

#include <WinSock2.h>
#include <Kinect.h>

#include "ExternalUpdateCollection.h"
#include "FrameDesc.h"
#include "KinectFrame.h"
#include "KinectVideoDecompress.h"
#include "SimplePool.h"
#include "TrackIDManager.h"
#include "TypeBroadcaster.h"
#include "ValueArray.h"

class KinectFilePlayer :
	public ValueArray<long>
	, public ExternalUpdateCollection
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr> {
public:
	KinectFilePlayer(
		int poolDepth
		, BodySegments &bs
		, TrackIDManager &tidm
		, ICoordinateMapper &cm
		, ProcessingParameters &pp
		);
	~KinectFilePlayer();

	void open(wstring fileName);

	FrameDesc &getYUYFD();
	FrameDesc &getDepthFD();

	SimplePool<KinectFrame> &getKFPool();
	TrackIDManager &getTIDM();

	//ValueArray<long>
	size_t getNVals();

	long get(long index);

	bool hasMin(long index);
	bool hasMax(long index);

	long getMinVal(long index);
	long getMaxVal(long index);
	
protected:
	//ValueArray<long>
	void setProt(long index, long value);

	KinectVideoDecompress *_kvd;
	FrameDesc _yuyFD, _depthFD;

	SimplePool<KinectFrame> *_framePool;
};

#endif