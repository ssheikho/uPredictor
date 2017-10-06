#include "KinectCloudWindow.h"
#include "RenderToggler.h"
#include "ShutdownContainer.h"

KinectCloudWindow::KinectCloudWindow(
	KinectInterface &ki
	, KIFBroadcaster &kb
	, ShutdownContainer &sc) :
	_window("3D View")
	, _r2d3d(ki.getColorFD(), ki.getDepthFD())
	, _kiftokp(&ki, 5)
	, _kcr(&_r2d3d)
{
	/*
	kb.addKIFR(&_kiftokp);
	_kiftokp.addKPR(&_r2d3d);
	_window.getRenderToggler().add(GLFW_KEY_C, &_kcr);
	sc.addChainedSI(&_window);
	*/
}

KinectCloudWindow::~KinectCloudWindow() {}

GLFWWindowWrapper &KinectCloudWindow::getWindow() {
	return _window;
}