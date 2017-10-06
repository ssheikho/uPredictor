#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
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
#include "ShutdownContainer.h"
#include "SimplePool.h"
#include "TBEUQueue.h"

#include <mfapi.h>

#include <tchar.h>

#include <queue>

using namespace std;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	ShutdownContainer sc;
	RecNameCollection rnc(L"D:\\\\test\\");

	BodySegments bs;
	TrackIDManager tidm;
	ProcessingParameters procParam(8000);
	KinectInterface ki(0, bs, tidm, procParam);
	ki.resetTimestamps();

	queue<SimplePool<KinectFrame>::PooledPtr> q;
	for (int i = 0; i < 120; i++)
		q.push(ki.getKFPool().getInstance());

	ProcessPipework<SimplePool<KinectFrame>::PooledPtr> pp(
		ki.getKFPool().getAllocator());
	pp.addNamedPipelineAtRoot("YUV");
	pp.addProcToNamedPipeline("YUV", getKP(KP_CONVERT_YUV_2_BGR));
	pp.addNamedPipelineUnderParent("YUV", "DEPTH");
	pp.addProcToNamedPipeline("DEPTH", getKP(KP_CONVERT_DEPTH_2_BGR));
	pp.addNamedPipelineUnderParent("YUV", "BODY_PTS");
	pp.addProcToNamedPipeline("BODY_PTS", getKP(KP_COMPUTE_BODY_CAMERA_SPACE_PTS));
	pp.addNamedPipelineUnderParent("BODY_PTS", "BODY_PTS_HD");
	pp.addNamedPipelineUnderParent("BODY_PTS", "BODY_PTS_DEPTH");
	pp.addProcToNamedPipeline("BODY_PTS_HD", getKP(KP_COMPUTE_BODY_COLOR_SPACE_PTS));
	pp.addProcToNamedPipeline("BODY_PTS_DEPTH", getKP(KP_COMPUTE_BODY_DEPTH_SPACE_PTS));
	pp.addNamedPipelineUnderParent("BODY_PTS_HD", "BODY_PTS_HD_IMG");
	pp.addNamedPipelineUnderParent("BODY_PTS_DEPTH", "BODY_PTS_DEPTH_IMG");
	pp.addProcToNamedPipeline("BODY_PTS_HD_IMG"
		,getKP(KP_RENDER_BODY_ON_HD_BGR_IMAGE));
	pp.addProcToNamedPipeline("BODY_PTS_DEPTH_IMG"
		, getKP(KP_RENDER_BODY_ON_DEPTH_BGR_IMAGE));
	pp.addNamedPipelineUnderParent("YUV", "DEPTH_PTS");
	pp.addProcToNamedPipeline("DEPTH_PTS", getKP(KP_COMPUTE_DEPTH_CAMERA_SPACE_PTS));
	pp.addProcToNamedPipeline("DEPTH_PTS", getKP(KP_COMPUTE_DEPTH_COLOR_SPACE_PTS));
	pp.addNamedPipelineUnderParent("DEPTH_PTS", "DEPTH_REG");
	pp.addProcToNamedPipeline("DEPTH_REG", getKP(KP_COMPUTE_PT_REGISTRATION));

	ki.addRecipient(&pp.getRoot());
	
	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);
	
	KinectCloudRender kcr(KinectCloudRender::KR_COLOR_CLOUD_MODE
		, ki.getKFPool().getAllocator(), ki.getDepthFD().h * ki.getDepthFD().w);
	window.getRenderToggler().add(GLFW_KEY_C, &kcr);
	//pp.addRecipient(&kcr);
	//q.TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::addRecipient(&kcr);
	pp.addRecipientToNamedPipeline("DEPTH_REG", &kcr);

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
	KFBGRChannel hdChan(0, KinectFrame::KinectFrameHDBGR::KF_HD_BGR_BODIES);
	//q.TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::addRecipient(&hdChan);
	//ki.addRecipient(&hdChan);
	pp.addRecipientToNamedPipeline("BODY_PTS_HD_IMG", &hdChan);
	hdChan.addRecipient(&hdIW);
	sc.addChainedSI(&hdW);

	AutoResizeWindow depthW(hInstance, 100, 100);
	ImageWindow depthIW(&depthW, ki.getDepthFD().w, ki.getDepthFD().h, L"Depth Image");
	KFBGRChannel depthChan(0, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_BGR_BODIES);
	//q.TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::addRecipient(&depthChan);
	//ki.addRecipient(&depthChan);
	pp.addRecipientToNamedPipeline("BODY_PTS_DEPTH_IMG", &depthChan);
	depthChan.addRecipient(&depthIW);
	sc.addChainedSI(&depthW);

	shared_ptr<KinectVideoCompress> kvc =
		shared_ptr<KinectVideoCompress>(new KinectVideoCompress());
	kvc->open(rnc.getCamFilename(0), ki.getYUYFD());
	pp.addNamedPipelineUnderParent("YUV", "HDC");
	pp.addProcToNamedPipeline("HDC", kvc);

	//q.TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::addRecipient(&kvc);
	//ki.addRecipient(&kvc);

	shared_ptr<KinectDepthCompress> kdc =
		shared_ptr<KinectDepthCompress>(new KinectDepthCompress());
	kdc->open(rnc.get3DFilename(0), ki.getDepthFD());
	pp.addNamedPipelineAtRoot("DEPTHC");
	pp.addProcToNamedPipeline("DEPTHC", kdc);

	//q.TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>::addRecipient(&kdc);
	//ki.addRecipient(&kdc);

	pp.start();
	//q.start();
	ki.start();

	while (sc.isRunning())	window.render();

	kvc->close();
	kdc->close();

	//ki.join();
	//q.stop();
	
	exit(EXIT_SUCCESS);
}

