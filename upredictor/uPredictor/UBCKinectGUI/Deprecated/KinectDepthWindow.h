#ifndef KINECT_DEPTH_WINDOW_H
#define KINECT_DEPTH_WINDOW_H

#include <WinSock2.h>
#include <Kinect.h>

#include "AutoResizeWindow.h"
#include "ImageWindow.h"
#include "KIFAddBodyCameraPts.h"
#include "KIFAddBodyDepthPts.h"
#include "KIFAddDepthVideo.h"
#include "KIFBodyDepthRender2D.h"
#include "KFRToVR.h"

class KinectInterface;
class PoolRegistry;
class ShutdownContainer;

class KinectDepthWindow {
public:
	KinectDepthWindow(
		HINSTANCE hInstance
		, PoolRegistry *pr
		, KinectInterface &ki
		, KIFBroadcaster &kb
		, ShutdownContainer &sc
		);
	~KinectDepthWindow();

protected:
	AutoResizeWindow _arwD;
	KIFAddDepthVideo _kiftdv;
	KIFAddBodyCameraPts _kifabcp;
	KIFAddBodyDepthPts _kifabdp;
	KIFBodyDepthRender2D _kiabdi2d;
	KFRToVR _kfrtovrD;
	ImageWindow _iwD;
};

#endif