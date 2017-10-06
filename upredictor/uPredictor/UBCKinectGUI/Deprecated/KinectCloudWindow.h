#ifndef KINECT_CLOUD_WINDOW_H
#define KINECT_CLOUD_WINDOW_H

#include "GLFWWindowWrapper.h"
#include "KIFToKP.h"
#include "KinectCloudRender.h"
#include "Registration2D3D.h"
#include "ShutdownContainer.h"

class KinectCloudWindow {
public:
	KinectCloudWindow(
		KinectInterface &ki
		, KIFBroadcaster &kb
		, ShutdownContainer &sc);
	~KinectCloudWindow();

	GLFWWindowWrapper &getWindow();

protected:
	GLFWWindowWrapper _window; //3D Window Setup
	Registration2D3D _r2d3d;
	KIFToKP _kiftokp;
	KinectCloudRender _kcr;
};

#endif