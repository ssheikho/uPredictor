#ifndef KINECT_INTERFACE_H
#define KINECT_INTERFACE_H

#include <WinSock2.h>
#include <Kinect.h>

#include "ExternalUpdate.h"
#include "ExternalUpdateCollection.h"
#include "ExternalUpdateThread.h"
#include "FrameDesc.h"
#include "KinectFrame.h"
//#include "ObjectBroadcaster.h"
#include "Pause.h"
#include "PauseUntilDone.h"
#include "RefCountedPtr.h"
#include "TypeBroadcaster.h"
#include "SimplePool.h"
#include "TrackIDManager.h"

//#include <opencv/cv.hpp>

#include <vector>

using namespace std;

class KinectFrameFactory;
class KinectImageFrameRecipient;
class PoolRegistry;
class ProcessingParameters;

class KinectInterface :
	public ExternalUpdate
	, public ExternalUpdateCollection
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>
	//, public TypeBroadcaster<shared_ptr<KinectFrame>>
{
public:
	KinectInterface(
		UINT64 kinectIndex
		, BodySegments &bs
		, TrackIDManager &tidm
		, ProcessingParameters &pp
		, bool pauseUntilDone = false
		);
	~KinectInterface();

	void update();
	bool hasFutureUpdates();
	void onStartup();

	void start();
	void join();
	
	FrameDesc &getYUYFD();
	FrameDesc &getDepthFD();

	SimplePool<KinectFrame> &getKFPool();
	//TrackIDManager &getTIDM();

	ICoordinateMapper &getCoordinateMapper();

	void resetTimestamps();

	UINT64 kinectIndex();

	Pause &getPause();
	PauseUntilDone<SimplePool<KinectFrame>::PooledPtr> &getPauseUntilDone();

protected:
	HRESULT initializeDefaultSensor();

	UINT64 _kinectIndex;
	Pause _pause;

	bool _running;
	ExternalUpdateThread _eut;

	long _frameNo;
	TIMESPAN _tareStamp;

	IKinectSensor *_kinectSensor;
	WCHAR _kinectUniqeID[256];

	IMultiSourceFrameReader *_frameReader;
	ICoordinateMapper *_coordinateMapper;
	WAITABLE_HANDLE _frameWH;

	FrameDesc _yuyFD, _depthFD;
	KinectFrameFactory *_kff;

	SimplePool<KinectFrame> *_framePool;

	PauseUntilDone<SimplePool<KinectFrame>::PooledPtr> _pauseUntil;
	bool _pauseUntilDone;
	FILETIME _lastTime;
};

#endif