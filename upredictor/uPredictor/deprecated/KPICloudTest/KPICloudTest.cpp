#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
#include "ColumnLayout.h"
#include "CUDAColorSegInterface.h"
//#include "CUDAColorTrackerGUI.h"
//#include "ExternalQueuePair.h"
//#include "ExternalQueuePairProcessor.h"
#include "GLFWWindowWrapper.h"
#include "ImageWindow.h"
//#include "ImageWindowAndChannel.h"
#include "KinectCloudRender.h"
#include "KinectFrame.h"
#include "KinectPlaybackInterface.h"
#include "KinectProcess.h"
#include "ProcessingParameters.h"
#include "ProcessPipework.h"
#include "RenderToggler.h"
#include "RowLayout.h"
//#include "SegmentBroadcaster.h"
#include "ShutdownContainer.h"
#include "SimpleLabeledSlider.h"
#include "SimplePool.h"
#include "TrackIDManager.h"

#include <tchar.h>

//TEST
class Player : public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<cv::Mat>
{
public:
	void processType(SimplePool<KinectFrame>::PooledPtr t)
	{
		//fireUpdate(t->getImageChannel(0, 0));
		fireUpdate(t->_bgr);
	}
	void onStartup() {}
};

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	HINSTANCE cudaDLL = LoadLibrary(L"UBCColorTrackCUDA.dll");

	ShutdownContainer sc;
	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);

	BodySegments bs;
	TrackIDManager tidm;
	ProcessingParameters procParam(8000);

	KinectPlaybackInterface kpi(L"testing", bs, tidm, procParam);

	ProcessPipework<SimplePool<KinectFrame>::PooledPtr> pp(
		kpi.getKFPool().getAllocator());
	pp.addNamedPipelineAtRoot("STEP_ONE");
	//pp.addProcToNamedPipeline("STEP_ONE", getKP(KP_CONVERT_YUV_2_BGR));
	pp.addProcToNamedPipeline("STEP_ONE"
		, getKP(KP_COMPUTE_DEPTH_CAMERA_SPACE_PTS));
	pp.addProcToNamedPipeline("STEP_ONE"
		, getKP(KP_COMPUTE_DEPTH_COLOR_SPACE_PTS));

	pp.addNamedPipelineUnderParent("STEP_ONE", "DEPTH_REG");
	pp.addProcToNamedPipeline("DEPTH_REG", getKP(KP_COMPUTE_PT_REGISTRATION));
	
	//pp.addNamedPipelineUnderParent("DEPTH_REG", "SEGMENTING");

	/*
	TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> cudaQ;
	ExternalQueuePairProcessor<SimplePool<KinectFrame>::PooledPtr> cudaQProc;
	cudaQ.TypeBroadcaster<
		ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>>::
		addRecipient(&cudaQProc);*/
	/*
	CUDAColorSegInterface ccsi(cudaDLL, kpi.getDepthFD().w, kpi.getDepthFD().h, 2);
	pp.addProcToNamedPipeline("SEGMENTING"
		, shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(
			&ccsi));*/
			
	AutoResizeWindow depthW(hInstance, 100, 100);
	sc.addChainedSI(&depthW);
	ColumnLayout cl(&depthW, 100, 255);
	RowLayout rl(&cl, 100, 255);

	SimpleLabeledSlider sls(&cl, 200, 100, 0, kpi.getYUYNFrames() - 1, 0, 1.0, true);
	sls.getSS().TypeBroadcaster<long>::addRecipient(&kpi);
	/*
	ImageWindowAndChannel depthColorIW(
		&rl, kpi.getDepthFD().w, kpi.getDepthFD().h, L"Depth Color Image"
		, KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_COLOR_BGR);
	pp.addRecipientToNamedPipeline("SEGMENTING", &depthColorIW.getChan());

	ImageWindow segIW(&rl, kpi.getDepthFD().w, kpi.getDepthFD().h, L"Depth Color Segments");
	SegmentBroadcaster sb(0);
	pp.addRecipientToNamedPipeline("SEGMENTING", &sb);
	sb.addRecipient(&segIW);*/

	KinectCloudRender kcr(
		KinectCloudRender::KR_SEGMENT_CLOUD_MODE
		, kpi.getKFPool().getAllocator(), kpi.getDepthFD().h * kpi.getDepthFD().w
		, 25);
	pp.addRecipientToNamedPipeline("DEPTH_REG", &kcr);
	window.getRenderToggler().add(GLFW_KEY_P, &kcr);

	// TESTING VIDEO PLAYBACK
	AutoResizeWindow test(hInstance, 100, 100);
	sc.addChainedSI(&test);
	ImageWindow iw(&test, kpi.getYUYFD().w, kpi.getYUYFD().h, L"IW");
	Player pl;
	pl.addRecipient(&iw);
	pp.addNamedPipelineUnderParent("DEPTH_REG", "IMAGE");
	pp.addProcToNamedPipeline("IMAGE", shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(
		&pl));

	//CUDAColorTrackerGUI cctg(&cl, &ccsi.getMTP());

	kpi.addRecipient(&pp.getRoot());
	//cudaQ.start();
	pp.start();

	while (sc.isRunning())	window.render();

	exit(EXIT_SUCCESS);
}