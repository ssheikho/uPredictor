#ifndef KINECT_HD_WINDOW_H
#define KINECT_HD_WINDOW_H

#include <WinSock2.h>
#include <Kinect.h>

#include "AutoResizeWindow.h"
#include "KFRToVR.h"
#include "KIFAddBodyCameraPts.h"
#include "KIFAddBodyColorPts.h"
#include "KIFBodyColorRender2D.h"
#include "ImageWindow.h"

class KIFBroadcaster;
class KinectHDWindow;
class PoolRegistry;
class ShutdownContainer;

struct FrameDesc;

class KinectHDWindow {
public:
	KinectHDWindow(
		HINSTANCE hInstance
		, PoolRegistry *pr
		, KinectInterface &ki
		, KIFBroadcaster &kb
		, ShutdownContainer &sc
		);
	~KinectHDWindow();

protected:
	AutoResizeWindow _arw;
	KIFAddBodyCameraPts _kifabcp;
	KIFAddBodyColorPts _kifabcolp;
	KIFBodyColorRender2D _kifabcoli2d;
	KFRToVR _kfrtovr;
	ImageWindow _iw;
};

#endif