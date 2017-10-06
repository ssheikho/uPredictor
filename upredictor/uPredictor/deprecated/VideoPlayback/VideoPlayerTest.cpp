#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "DepthVideoPlayback.h"
#include "GLFWWindowWrapper.h"
#include "ImageWindow.h"
#include "RowLayout.h"
#include "ProcessingParameters.h"
#include "ShutdownContainer.h"
#include "SimpleLabeledSlider.h"
#include "TrackIDManager.h"
#include "VideoPlayer.h"

#include <tchar.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {

	ShutdownContainer sc;
	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);

	/*
	BodySegments bs;
	TrackIDManager tidm;
	ProcessingParameters procParam(8000);
	DepthVideoPlayback dvp(L"depthtest", bs, tidm, procParam);
	AutoResizeWindow arw(hInstance, 1000, 1000);
	sc.addChainedSI(&arw);
	RowLayout rl(&arw, 1000, 1000);
	ImageWindow iw(&rl, 512, 424, L"Video Frame");
	dvp.addRecipient(&iw);
	SimpleLabeledSlider sls(&rl, 400, 100, 0, dvp.getNFrames(), 0, 1.0, true);
	sls.getSS().TypeBroadcaster<long>::addRecipient(&dvp);*/

	VideoPlayer vp(L"test3.avi");

	AutoResizeWindow arw(hInstance, vp._w + 500, vp._h + 500);
	sc.addChainedSI(&arw);
	RowLayout rl(&arw, vp._w + 500, vp._h + 500);

	ImageWindow iw(&rl, vp._w, vp._h, L"Video Frame");

	SimpleLabeledSlider sls(&rl, 400, 100, 0, vp._frameCount, 0, 1.0, true);
	sls.getSS().TypeBroadcaster<long>::addRecipient(&vp);
	vp.addRecipient(&iw);

	while (sc.isRunning())	window.render();

	exit(EXIT_SUCCESS);
}