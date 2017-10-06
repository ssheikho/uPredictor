#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
#include "BoxAndConstellationFactory.h"
#include "ColorTracker.h"
#include "ColumnLayout.h"
#include "CUDAColorSegInterface.h"
#include "CUDAColorTrackerGUI.h"
#include "CUDAControl.h"
#include "CUDANormalField.h"
#include "ExternalQueuePairProcessor.h"
#include "KinectDepthCompress.h"
#include "GLFWWindowWrapper.h"
#include "ImageChannelBroadcaster.h"
#include "ImageWindow.h"
#include "KFBGRChannel.h"
#include "KinectInterface.h"
#include "KinectProcess.h"
#include "ProcessingParameters.h"
#include "ProcessPipework.h"
#include "RowLayout.h"
#include "ShutdownContainer.h"
#include "SubsetPt3DCollectionFactory.h"
#include "TrackIDManager.h"
#include "VideoRecorder.h"

#include <tchar.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	HINSTANCE cudaDLL = LoadLibrary(L"UBCColorTrackCUDA.dll");
	setupCUDA(cudaDLL);

	ShutdownContainer sc;
	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);
	
	BodySegments bs;
	TrackIDManager tidm;
	ProcessingParameters procParam(8000);
	KinectInterface ki(0, bs, tidm, procParam, true);
	ki.resetTimestamps();

	ProcessPipework<SimplePool<KinectFrame>::PooledPtr> pp(
		ki.getKFPool().getAllocator());
	pp.addNamedPipelineAtRoot("STEP_ONE");
	pp.addProcToNamedPipeline("STEP_ONE", getKP(KP_CONVERT_YUV_2_BGR));
	pp.addProcToNamedPipeline("STEP_ONE"
		, getKP(KP_COMPUTE_DEPTH_CAMERA_SPACE_PTS));
	pp.addProcToNamedPipeline("STEP_ONE"
		, getKP(KP_COMPUTE_DEPTH_COLOR_SPACE_PTS));

	pp.addNamedPipelineUnderParent("STEP_ONE", "DEPTH_REG");
	pp.addProcToNamedPipeline("DEPTH_REG", getKP(KP_COMPUTE_PT_REGISTRATION));

	pp.addNamedPipelineUnderParent("DEPTH_REG", "SEGMENTING");

	TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> cudaQ;
	ExternalQueuePairProcessor<SimplePool<KinectFrame>::PooledPtr> cudaQProc;
	cudaQ.TypeBroadcaster<
		ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>>::
		addRecipient(&cudaQProc);

	CUDAColorSegInterface ccsi(cudaDLL, ki.getDepthFD().w, ki.getDepthFD().h
		, 3, cudaQ);
	pp.addProcToNamedPipeline("SEGMENTING"
		, shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(
			&ccsi));

	CUDANormalField cnf(cudaDLL, ki.getDepthFD().w, ki.getDepthFD().h, cudaQ);
	//pp.addProcToNamedPipeline("SEGMENTING"
	//	, shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(
	//		&cnf));

	AutoResizeWindow depthW(hInstance, 100, 100);
	sc.addChainedSI(&depthW);
	ColumnLayout cl(&depthW, 100, 255);
	RowLayout rl(&cl, 100, 255);

	ImageWindow depthColorIW(
		&rl, ki.getDepthFD().w, ki.getDepthFD().h, L"Depth Color Image");
	KFBGRChannel depthColorChan(
		KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_COLOR_BGR);
	pp.addRecipientToNamedPipeline("SEGMENTING", &depthColorChan);
	depthColorChan.addRecipient(&depthColorIW);

	ImageWindow depthSegIW(
		&rl, ki.getDepthFD().w, ki.getDepthFD().h, L"Depth Seg Image");
	KFBGRChannel depthSegChan(
		KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_BGR_SEGMENTS);
	pp.addRecipientToNamedPipeline("SEGMENTING", &depthSegChan);
	depthSegChan.addRecipient(&depthSegIW);
	
	FrameDesc fd = ki.getDepthFD();
	SubsetPt3DCollectionFactory apcf(fd.w * fd.h);
	SimplePool<SubsetPt3DCollection> apcp(apcf, 100);
	BoxAndConstellationFactory bacf(apcp.getAllocator());
	SimplePool<BoxAndConstellation> bacp(bacf, 100);
	ColorTracker ct(
		fd
		, bacp.getAllocator()
		, KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR
		, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_COLOR_BGR
		, ki.getKFPool().getAllocator());
	
	VideoRecorder vr(L"test.avi", fd);
	ct.getICB().addRecipient(&vr);

	pp.addNamedPipelineUnderParent("SEGMENTING", "TO_AVI");
	pp.addProcToNamedPipeline("TO_AVI",
		shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(&ct));
		
	/*KinectDepthCompress kdc(L"depthtest", fd);
	pp.addNamedPipelineUnderParent("SEGMENTING", "TO_AVI");
	pp.addProcToNamedPipeline("TO_AVI",
		shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(&kdc));*/

	CUDAColorTrackerGUI cctg(&cl, &ccsi.getMTP());

	ki.addRecipient(&pp.getRoot());
	cudaQ.start();
	pp.start();
	ki.start();

	while (sc.isRunning())	window.render();

	//kdc.close();

	exit(EXIT_SUCCESS);
}

