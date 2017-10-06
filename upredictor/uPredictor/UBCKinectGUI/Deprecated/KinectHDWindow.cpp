#include "KinectHDWindow.h"
#include "KinectInterface.h"
#include "ShutdownContainer.h"

KinectHDWindow::KinectHDWindow(
	HINSTANCE hInstance
	, PoolRegistry *pr
	, KinectInterface &ki
	, KIFBroadcaster &kb
	, ShutdownContainer &sc) :
	_arw(hInstance, 100, 100)
	, _kifabcp(pr, 30)
	, _kifabcolp(pr, 30, ki.getCoordinateMapper())
	, _kifabcoli2d(pr, &ki, true)
	, _iw(&_arw, ki.getColorFD(), L"HD Image")
{
	kb.addKIFR(&_kfrtovr);
	//pull camera pts out entirely 
	_kifabcp.addKIFR(&_kifabcolp);
	_kifabcolp.addKIFR(&_kifabcoli2d);
	sc.addChainedSI(&_arw);

	_kifabcoli2d.addKIFR(&_kfrtovr);
	_kfrtovr.addVR(&_iw);
}

KinectHDWindow::~KinectHDWindow() {}