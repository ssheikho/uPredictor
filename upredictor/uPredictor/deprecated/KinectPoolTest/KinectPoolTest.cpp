#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
#include "ColumnLayout.h"
#include "FrameRateCounter.h"
#include "GLFWWindowWrapper.h"
#include "ImageWindow.h"
#include "KFBGRChannel.h"
#include "KinectCloudRender.h"
#include "KinectInterface.h"
#include "KinectDepthCompress.h"
#include "KinectProcess.h"
#include "KinectVideoCompress.h"
#include "NumberInfoList.h"
#include "ORToEU.h"
#include "ProcessingParameters.h"
#include "ProcessPipework.h"
#include "RecNameCollection.h"
#include "RefCountedPtr.h"
#include "RenderToggler.h"
#include "RowLayout.h"
#include "ShutdownContainer.h"
#include "SimpleLabeledSlider.h"
#include "SimplePool.h"
#include "TBEUQueue.h"

#include <mfapi.h>

#include <tchar.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	ShutdownContainer sc;
	RecNameCollection rnc(L"D:\\\\test\\");

	BodySegments bs;
	TrackIDManager tidm;

	ProcessingParameters procParam(2350);
	KinectInterface ki(0, 100, bs, tidm, procParam);
	ki.resetTimestamps();

	ProcessPipework<SimplePool<KinectFrame>::PooledPtr> pp(100);
	pp.addNamedPipelineAtRoot("YUV");
	pp.addProcToNamedPipeline("YUV", getKP(KP_CONVERT_YUV_2_BGR));
	/*
	pp.addProcToNamedPipeline("YUV", getKP(KP_CONVERT_DEPTH_2_BGR));
	pp.addNamedPipelineUnderParent("YUV", "BODY_PTS");
	pp.addProcToNamedPipeline("BODY_PTS", getKP(KP_COMPUTE_BODY_CAMERA_SPACE_PTS));
	pp.addNamedPipelineUnderParent("BODY_PTS", "BODY_PTS_HD");
	pp.addNamedPipelineUnderParent("BODY_PTS", "BODY_PTS_DEPTH");
	pp.addProcToNamedPipeline("BODY_PTS_HD", getKP(KP_COMPUTE_BODY_COLOR_SPACE_PTS));
	pp.addProcToNamedPipeline("BODY_PTS_DEPTH", getKP(KP_COMPUTE_BODY_DEPTH_SPACE_PTS));
	pp.addNamedPipelineUnderParent("BODY_PTS_HD", "BODY_PTS_HD_IMG");
	pp.addNamedPipelineUnderParent("BODY_PTS_DEPTH", "BODY_PTS_DEPTH_IMG");
	pp.addProcToNamedPipeline("BODY_PTS_HD_IMG"
		, getKP(KP_RENDER_BODY_ON_HD_BGR_IMAGE));
	pp.addProcToNamedPipeline("BODY_PTS_DEPTH_IMG"
		, getKP(KP_RENDER_BODY_ON_DEPTH_BGR_IMAGE));
	pp.addNamedPipelineUnderParent("YUV", "DEPTH_PTS");
	pp.addProcToNamedPipeline("DEPTH_PTS", getKP(KP_COMPUTE_DEPTH_CAMERA_SPACE_PTS));
	pp.addProcToNamedPipeline("DEPTH_PTS", getKP(KP_COMPUTE_DEPTH_COLOR_SPACE_PTS));
	pp.addNamedPipelineUnderParent("DEPTH_PTS", "DEPTH_REG");
	pp.addProcToNamedPipeline("DEPTH_REG", getKP(KP_COMPUTE_PT_REGISTRATION));

	pp.addNamedPipelineAtRoot("DEPTHL");
	pp.addNamedPipelineUnderParent("DEPTHL", "DEPTHLBGR");
	pp.addProcToNamedPipeline("DEPTHL", getKP(KP_COMPUTE_DEPTH_L));
	pp.addProcToNamedPipeline("DEPTHLBGR", getKP(KP_CONVERT_DEPTH_L_2_BGR));
	*/

	ki.addRecipient(&pp.getRoot());

	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);

	/*
	KinectCloudRender kcr;
	window.getRenderToggler().add(GLFW_KEY_C, &kcr);
	pp.addRecipientToNamedPipeline("DEPTH_REG", &kcr);
	*/

	//ORToEU<shared_ptr<KinectFrame>> frameRateInput;
	AutoResizeWindow frameRateWindow(hInstance, 100, 100);
	NumberInfoList frameRates(&frameRateWindow, 100, 100);
	sc.addChainedSI(&frameRateWindow);

	FrameRateCounter frcKI;
	ki.addEU(&frcKI);
	frameRates.addDoubleLabel(L"Frame Rate KI:", &frcKI);
	frameRates.addLongLabel(L"Pool Ready:", &ki.getKFPool());

	AutoResizeWindow depthW(hInstance, 100, 100);
	ColumnLayout depthCL(&depthW, 100, 100);
	RowLayout depthRL(&depthCL, 100, 100);

	ImageWindow depthIW(&depthRL, ki.getYUYFD().w, ki.getYUYFD().h, L"HD Image");
	KFBGRChannel depthChan(KinectFrame::KinectFrameBGR::KF_BGR_HD);
	pp.addRecipientToNamedPipeline("YUV", &depthChan);
	depthChan.addRecipient(&depthIW);

	sc.addChainedSI(&depthW);

	pp.start();
	ki.start();

	while (sc.isRunning())	window.render();

	exit(EXIT_SUCCESS);
}

