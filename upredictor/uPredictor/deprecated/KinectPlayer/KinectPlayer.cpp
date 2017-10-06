#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
#include "FrameRateCounter.h"
#include "GLFWWindowWrapper.h"
#include "ImageWindow.h"
#include "KFBGRChannel.h"
#include "KinectFilePlayer.h"
#include "KinectInterface.h"
#include "KinectVideoCompress.h"
#include "LongValueArrayEU.h"
#include "NumberInfoList.h"
#include "ORToEU.h"
#include "ProcessingParameters.h"
#include "RecNameCollection.h"
#include "RefCountedPtr.h"
#include "ShutdownContainer.h"
#include "SimplePool.h"
#include "TBEUQueue.h"

#include <mfapi.h>

#include <tchar.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	/*
	ShutdownContainer sc;
	RecNameCollection rnc(L"D:\\\\test\\");

	BodySegments bs;
	TrackIDManager tidm;
	KinectInterface kinect(0, 100, bs, tidm);

	ProcessingParameters pp(8000);
	KinectFilePlayer ki(100, bs, tidm, kinect.getCoordinateMapper(), pp);
	//ki.open(L"D:\\\\test\\bird.avi");
	ki.open(rnc.getCamFilename(0));
	LongValueArrayEU lvaeu(&ki, 0, true);
	ExternalUpdateThread eut(lvaeu);
	//ki.resetTimestamps();

	//TBEUQueue<SimplePool<KinectFrame>::PooledPtr> q;
	//ki.addRecipient(&q);

	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);

	//ORToEU<shared_ptr<KinectFrame>> frameRateInput;
	AutoResizeWindow frameRateWindow(hInstance, 100, 100);
	NumberInfoList frameRates(&frameRateWindow, 100, 100);
	sc.addChainedSI(&frameRateWindow);

	FrameRateCounter frcKI, frcKQ;
	ki.addEU(&frcKI);
	//q.addEU(&frcKQ);
	frameRates.addDoubleLabel(L"Frame Rate KI:", &frcKI);
	frameRates.addDoubleLabel(L"Frame Rate Q:", &frcKQ);
	//frameRates.addLongLabel(L"Q Depth:", &q);
	frameRates.addLongLabel(L"Pool Ready:", &ki.getKFPool());

	AutoResizeWindow hdW(hInstance, 100, 100);
	ImageWindow hdIW(&hdW, ki.getYUYFD().w, ki.getYUYFD().h, L"HD Image");
	KFBGRChannel hdChan(KinectFrame::KinectFrameBGR::KF_BGR_HD);
	//q.TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::addRecipient(&hdChan);
	ki.TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::addRecipient(&hdChan);
	//ki.addRecipient(&hdChan);
	//hdChan.addRecipient(&hdIW);
	sc.addChainedSI(&hdW);

	//q.start();
	//ki.start();
	eut.start();

	while (sc.isRunning())	window.render();

	//ki.join();
	//q.stop();
	eut.stop();

	exit(EXIT_SUCCESS);
	*/
}

