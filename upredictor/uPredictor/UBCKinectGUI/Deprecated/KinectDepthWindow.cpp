#include "KinectDepthWindow.h"
#include "KinectInterface.h"
#include "ShutdownContainer.h"

KinectDepthWindow::KinectDepthWindow(
	HINSTANCE hInstance
	, PoolRegistry *pr
	, KinectInterface &ki
	, KIFBroadcaster &kb
	, ShutdownContainer &sc
	) :
	_arwD(hInstance, 100, 100)
	, _kiftdv(pr, ki.getDepthFD())
	, _kifabcp(pr, 30)
	, _kifabdp(pr, 30, ki.getCoordinateMapper())
	, _kiabdi2d(pr, &ki, true)
	, _kfrtovrD(KinectImageFrame::KIF_DEPTH_8UC4_BGRA_WITH_BODY_POINTS)
	, _iwD(&_arwD, _kiftdv.getFD(), L"Depth Image")
{
	kb.addKIFR(&_kiftdv);
	_kiftdv.addKIFR(&_kifabcp);
	_kifabcp.addKIFR(&_kifabdp);
	_kifabdp.addKIFR(&_kiabdi2d);
	sc.addChainedSI(&_arwD);

	_kiabdi2d.addKIFR(&_kfrtovrD);
	_kfrtovrD.addVR(&_iwD);
}

KinectDepthWindow::~KinectDepthWindow() {}