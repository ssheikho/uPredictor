#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
#include "ColumnLayout.h"
#include "GLFWWindowWrapper.h"
#include "ImageWindow.h"
#include "KFBGRChannel.h"
#include "KinectInterface.h"
#include "KinectProcess.h"
#include "ProcessingParameters.h"
#include "ProcessPipework.h"
#include "RangeInterface.h"
#include "RowLayout.h"
#include "ShutdownContainer.h"
#include "SimplePool.h"


#include <mfapi.h>

#include <tchar.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	ShutdownContainer sc;

	BodySegments bs;
	TrackIDManager tidm;
	ProcessingParameters procParam(8000);
	KinectInterface ki(0, bs, tidm, procParam);
	ki.resetTimestamps();

	ProcessPipework<SimplePool<KinectFrame>::PooledPtr> pp(
		ki.getKFPool().getAllocator());
	pp.addNamedPipelineAtRoot("STEP_ONE");

	pp.addNamedPipelineUnderParent("STEP_ONE", "DEPTH_REG");

	pp.addProcToNamedPipeline("STEP_ONE", getKP(KP_CONVERT_YUV_2_BGR));
	pp.addProcToNamedPipeline("STEP_ONE", getKP(KP_COMPUTE_DEPTH_32_FC1));
	pp.addProcToNamedPipeline("STEP_ONE", getKP(KP_COMPUTE_DEPTH_CAMERA_SPACE_PTS));
	pp.addProcToNamedPipeline("STEP_ONE", getKP(KP_COMPUTE_DEPTH_COLOR_SPACE_PTS));

	pp.addProcToNamedPipeline("DEPTH_REG", getKP(KP_COMPUTE_PT_REGISTRATION));

	ki.addRecipient(&pp.getRoot());

	AutoResizeWindow hdW(hInstance, 100, 100);
	sc.addChainedSI(&hdW);
	ColumnLayout cl(&hdW, 100, 255);
	RowLayout rl(&cl, 100, 255);

	ImageWindow depthColorIW(
		&rl, ki.getDepthFD().w, ki.getDepthFD().h, L"Depth Color Image");
	KFBGRChannel depthColorChan(
		KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_COLOR_BGR);
	pp.addRecipientToNamedPipeline("DEPTH_REG", &depthColorChan);
	depthColorChan.addRecipient(&depthColorIW);


	RangeInterface ri(&cl, ki.getKFPool().getAllocator());

	depthColorIW.TypeBroadcaster<pair<int, int>>::addRecipient(&ri);

	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);

	pp.start();
	ki.start();

	while (sc.isRunning())	window.render();

	exit(EXIT_SUCCESS);


}

