#ifndef KINECT_INTERFACE_H
#define KINECT_INTERFACE_H

#include "CameraModel.h"
#include "ExternalUpdate.h"
#include "ExternalUpdateCollection.h"
#include "ExternalUpdateThread.h"
#include "FakeWindowsTypes.h"
#include "FrameDesc.h"
#include "KinectFrame.h"
//#include "ObjectBroadcaster.h"
#include "Pause.h"
#include "RefCountedPtr.h"
#include "TypeBroadcaster.h"
#include "SimplePool.h"
#include "TrackIDManager.h"

#include <frame_listener_impl.h>
#include <libfreenect2.hpp>
#include <registration.h>

//#include <opencv/cv.hpp>

#include <vector>

using namespace std;

class KinectFrameFactory;
class KinectImageFrameRecipient;
class PoolRegistry;
class ProcessingParameters;

class KinectInterface :
	public ExternalUpdate
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>
{
public:
	KinectInterface(TrackIDManager &tidm, string serial = "");
	~KinectInterface();

	//public ExternalUpdate
	void update();
	bool hasFutureUpdates();
	void onStartup();

	void start();
	void join();
	
	FrameDesc &getBGRAFD();
	FrameDesc &getDepthFD();
	CameraModel &getDepthCM();

	SimplePool<KinectFrame> &getKFPool();

	libfreenect2::Registration &getCoordinateMapper();

	Pause &getPause();

	ExternalUpdateCollection &getRecipients();

protected:
	void initializeSensor();

	Pause _pause;
	bool _running;
	ExternalUpdateThread _eut;

	long _frameNo;
	
	std::string _serial;
	libfreenect2::Freenect2 _freenect2;
	libfreenect2::Freenect2Device *_kinectSensor;
	libfreenect2::PacketPipeline *_pipeline;
	libfreenect2::Registration *_coordinateMapper;
	libfreenect2::SyncMultiFrameListener *_listener;
	libfreenect2::FrameMap *_frames;


	FrameDesc _bgraFD, _depthFD;
	CameraModel *_depthCM;
	KinectFrameFactory *_kff;

	SimplePool<KinectFrame> *_framePool;
	ExternalUpdateCollection _recipients;
};

#endif
