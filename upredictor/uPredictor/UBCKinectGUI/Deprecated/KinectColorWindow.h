#ifndef KINECT_COLOR_WINDOW_H
#define KINECT_COLOR_WINDOW_H

#include <WinSock2.h>
#include <Kinect.h>

#include "AutoResizeWindow.h"
#include "ImageWindow.h"
#include "KIFAddBodyCameraPts.h"
#include "KIFAddBodyColorPts.h"
#include "KIFAddDepthVideo.h"
#include "KIFBodyColorRender2D.h"
#include "KFRToVR.h"

class KinectInterface;
class ShutdownContainer;

class KinectColorWindow {
public:
	KinectColorWindow(
		HINSTANCE hInstance
		, KinectInterface &ki
		, KIFBroadcaster &kb
		, ShutdownContainer &sc
		);
	~KinectColorWindow();

protected:
	AutoResizeWindow _arwD;
	KIFAddDepthVideo _kiftdv;
	KIFAddBodyCameraPts _kifabcp;
	KIFAddBodyColorPts _kifabdp;
	KIFBodyColorRender2D _kiabdi2d;
	KFRToVR _kfrtovrD;
	ImageWindow _iwD;
};

#endif