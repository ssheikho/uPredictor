#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include <GL/glew.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
#include "Box3DRenderer.h"
#include "ColumnLayout.h"
#include "CUDAColorSegInterface.h"
#include "CUDAColorTrackerGUI.h"
#include "CUDAControl.h"
#include "CUDANormalField.h"
#include "CUDASphereGridFilter.h"
#include "ExternalQueuePairProcessor.h"
#include "GLFWWindowWrapper.h"
#include "ImageWindowAndChannel.h"
#include "KinectInterface.h"
#include "KinectProcess.h"
#include "KinectCloudRender.h"
#include "KinectQuiverRenderer.h"
#include "KinectSphereRenderer.h"
#include "ProcessingParameters.h"
#include "ProcessPipework.h"
#include "RenderToggler.h"
#include "RowLayout.h"
#include "SegmentBroadcaster.h"
#include "ShutdownContainer.h"
#include "SimpleLabeledSlider.h"
#include "TrackIDManager.h"
//#include "UBCDARTModelRenderer.h"

#include "assimp_mesh_reader.h"
#include "tracker.h"

#include <cuda_gl_interop.h>
#include "cuda_runtime.h"

#include <tchar.h>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {

	//HINSTANCE cudaDLL = LoadLibrary(L"UBCColorTrackCUDA.dll");
	//setupCUDA();

	ShutdownContainer sc;
	GLFWWindowWrapper window("Pt Cloud");
	sc.addChainedSI(&window);

	glewInit();
	int dev = setDevice();
	cudaGLSetGLDevice(dev);
	cudaDeviceReset();
	
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
	pp.addNamedPipelineUnderParent("SEGMENTING", "SPHERE_FITTING");

	TBEUQueue<ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>> cudaQ;
	ExternalQueuePairProcessor<SimplePool<KinectFrame>::PooledPtr> cudaQProc;
	cudaQ.TypeBroadcaster<
		ExternalQueuePair<SimplePool<KinectFrame>::PooledPtr>>::
		addRecipient(&cudaQProc);

	CUDAColorSegInterface ccsi(ki.getDepthFD().w, ki.getDepthFD().h, 3);
	pp.addProcToNamedPipeline("SEGMENTING"
		, shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(
			&ccsi));

	CUDASphereGridFilter csgf(20, ki.getDepthFD().w * ki.getDepthFD().h);
	pp.addProcToNamedPipeline("SPHERE_FITTING"
		, shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(
			&csgf));

	AutoResizeWindow depthW(hInstance, 100, 100);
	sc.addChainedSI(&depthW);
	ColumnLayout cl(&depthW, 100, 255);
	RowLayout rl(&cl, 100, 255);

	ImageWindowAndChannel depthColorIW(
		&rl, ki.getDepthFD().w, ki.getDepthFD().h, L"Depth Color Image"
		, KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_COLOR_BGR);
	pp.addRecipientToNamedPipeline("SEGMENTING", &depthColorIW.getChan());

	ImageWindow segIW(&rl, ki.getDepthFD().w, ki.getDepthFD().h, L"Depth Color Segments");
	SegmentBroadcaster sb(0);
	pp.addRecipientToNamedPipeline("SEGMENTING", &sb);
	sb.addRecipient(&segIW);
	
	KinectCloudRender kcr(
		KinectCloudRender::KR_SEGMENT_CLOUD_MODE
		//KinectCloudRender::KR_INLIER_CLOUD_MODE
		, ki.getKFPool().getAllocator(), ki.getDepthFD().h * ki.getDepthFD().w
		, 25);
	pp.addRecipientToNamedPipeline("SEGMENTING", &kcr);
	window.getRenderToggler().add(GLFW_KEY_P, &kcr);

	KinectSphereRenderer ksr(KinectSphereRenderer::KSR_MODE_TRACKER_GRID);
	ksr.setColor(0.5, 0.5, 0.5, 0.5);
	pp.addRecipientToNamedPipeline("SPHERE_FITTING", &ksr);
	window.getRenderToggler().add(GLFW_KEY_O, &ksr);

	Box3DRenderer b3Dr(Box3DRenderer::B3DR_MODE_SPHERE_BB);
	b3Dr.setColor(1, 0.5, 0.5, 0.5);
	pp.addRecipientToNamedPipeline("SPHERE_FITTING", &b3Dr);
	window.getRenderToggler().add(GLFW_KEY_L, &b3Dr);

	CUDAColorTrackerGUI cctg(&cl, &ccsi.getMTP());

	dart::AssimpMeshReader assimpMeshReader;
	dart::ModelRenderer renderer(&assimpMeshReader);
	//dart::Tracker tracker(&renderer);
	//tracker.addModel(
	//	"C:/Users/justi/Documents/Research/Code/upredictor/uPredictor/ThirdParty/dart/models/leftHand/leftHand.xml");
	//window.getRenderToggler().add(GLFW_KEY_M, &modelRenderer);

	ki.addRecipient(&pp.getRoot());
	cudaQ.start();
	pp.start();
	ki.start();

	//window.initializeRenderObjects();
	while (sc.isRunning())	window.render();

	exit(EXIT_SUCCESS);
}