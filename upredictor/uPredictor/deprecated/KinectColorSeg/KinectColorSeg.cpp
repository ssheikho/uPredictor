#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include "AutoResizeWindow.h"
#include "BodySegments.h"
#include "BoxAndConstellationFactory.h"
#include "Box3DRenderer.h"
#include "BoxRenderer.h"
#include "ColorTracker.h"
#include "ColorTrackerInterface.h"
#include "ColumnLayout.h"
#include "GLFWWindowWrapper.h"
#include "ImageWindow.h"
#include "KFBGRChannel.h"
#include "KinectCloudRender.h"
#include "KinectInterface.h"
#include "KinectProcess.h"
#include "KinectSphereRenderer.h"
#include "PauseUnpauseUI.h"
#include "ProcessingParameters.h"
#include "ProcessPipework.h"
#include "RecNameCollection.h"
#include "RenderToggler.h"
#include "RowLayout.h"
#include "ShutdownContainer.h"
#include "SimpleLabeledSlider.h"
#include "SimplePool.h"
#include "SimpleSphereFinder.h"
#include "SphereRenderer.h"
#include "SubsetPt3DCollectionFactory.h"
#include "TrackedObjectRenderer.h"

#include<gl/GLUT.h>

#include <mfapi.h>

#include <tchar.h>

//#include <vld.h> 

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow) {
	HINSTANCE simpleGeomDLL = LoadLibrary(L"UBCSimpleGeometry.dll");

	ShutdownContainer sc;
	RecNameCollection rnc(L"D:\\\\test\\");

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
	pp.addNamedPipelineUnderParent("SEGMENTING", "SPHEREFIT");

	/*
	pp.addNamedPipelineUnderParent("SEGMENTING", "BOXREND");
	pp.addNamedPipelineUnderParent("SEGMENTING", "COMPUTECLOUDS");
	pp.addNamedPipelineUnderParent("COMPUTECLOUDS", "SPHEREFIT");
	//pp.addNamedPipelineUnderParent("DEPTH_GRADS_BGR", "SEGMENTING");



	//pp.addProcToNamedPipeline("COMPUTECLOUDS"
	//	, getKP(KP_COMPUTE_BOX_AND_CLOUD_CLOUDS));

	//pp.addRecipientToNamedPipeline("SPHEREFIT", &ki.getPauseUntilDone());

		*/

	SimpleSphereFinder ssf(simpleGeomDLL, 10);
	ssf.updateRadius(0.04);
	pp.addProcToNamedPipeline("SPHEREFIT",
		shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(&ssf));

	AutoResizeWindow hdW(hInstance, 100, 100);
	sc.addChainedSI(&hdW);

	ImageWindow hdColorIW(
		&hdW, ki.getYUYFD().w, ki.getYUYFD().h, L"HD Color Image");
	KFBGRChannel hdColorChan(
		KinectFrame::KinectFrameImageSources::KF_SOURCE_HD_BGR,
		KinectFrame::KinectFrameHDBGR::KF_HD_BGR);
	hdColorChan.addRecipient(&hdColorIW);
	pp.addRecipientToNamedPipeline("SPHEREFIT", &hdColorChan);

	AutoResizeWindow depthW(hInstance, 100, 100);
	sc.addChainedSI(&depthW);
	ColumnLayout cl(&depthW, 100, 255);
	RowLayout rl(&cl, 100, 255);
	ImageWindow depthColorIW(
		&rl, ki.getDepthFD().w, ki.getDepthFD().h, L"Depth Color Image");
	KFBGRChannel depthColorChan(
		KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_COLOR_BGR);
	pp.addRecipientToNamedPipeline("SPHEREFIT", &depthColorChan);
	depthColorChan.addRecipient(&depthColorIW);

	SubsetPt3DCollectionFactory apcf(ki.getDepthFD().w * ki.getDepthFD().h);
	SimplePool<SubsetPt3DCollection> apcp(apcf, 100);
	BoxAndConstellationFactory bacf(apcp.getAllocator());
	SimplePool<BoxAndConstellation> bacp(bacf, 100);
	ColorTracker ct(
		ki.getDepthFD()
		, bacp.getAllocator()
		, KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR
		, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_COLOR_BGR
		, ki.getKFPool().getAllocator());

	ImageWindow depthCSIW(
		&rl, ki.getDepthFD().w, ki.getDepthFD().h, L"Seg Image");

	ColorTrackerInterface cti(&cl, ct, depthCSIW);
	pp.addProcToNamedPipeline("SEGMENTING",
		shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(&ct));
	ct.getICB().addRecipient(&depthCSIW);
	//depthColorIW.TypeBroadcaster<pair<int, int>>::addRecipient(
	//	&ct.getTRIntInt());
	//depthColorIW.TypeBroadcaster<DragRect>::addRecipient(&ct.getTRDragRect());
	
	GLFWWindowWrapper window("Pt Cloud");
	KinectCloudRender kcr(
		KinectCloudRender::KR_SEGMENT_CLOUD_MODE
		//KinectCloudRender::KR_INLIER_CLOUD_MODE
		, ki.getKFPool().getAllocator(), ki.getDepthFD().h * ki.getDepthFD().w
		, 25);
	window.getRenderToggler().add(GLFW_KEY_C, &kcr);
	pp.addRecipientToNamedPipeline("SPHEREFIT", &kcr);
	sc.addChainedSI(&window);

	KinectSphereRenderer sr;
	pp.addRecipientToNamedPipeline("SPHEREFIT", &sr);
	window.getRenderToggler().add(GLFW_KEY_P, &sr);
	/*

	//SphereRenderer sr(sphere);
	//sr.setColor(1.0f, 1.0f, 0.0f, 1.0f);

	*/

	TrackedObjectRenderer tor(ki.getKFPool().getAllocator());
	window.getRenderToggler().add(GLFW_KEY_M, &tor);
	pp.addRecipientToNamedPipeline("SPHEREFIT", &tor);

	Box3DRenderer bthreedr;
	window.getRenderToggler().add(GLFW_KEY_O, &bthreedr);
	pp.addRecipientToNamedPipeline("SPHEREFIT", &bthreedr);

	AutoResizeWindow poolDepthW(hInstance, 100, 100);
	UBCEntry poolDepthE(L"-", &poolDepthW, true, 100, 25);
	apcp.addRecipient(&poolDepthE);

	ki.addRecipient(&pp.getRoot());
	pp.start();
	ki.start();

	while (sc.isRunning())	window.render();

	exit(EXIT_SUCCESS);
}

/*
BoxRenderer br;
KFBGRChannel depthCSChan(
KinectFrame::KinectFrameImageSources::KF_SOURCE_DEPTH_BGR
, KinectFrame::KinectFrameDepthBGR::KF_DEPTH_BGR_SEGMENTS);
pp.addProcToNamedPipeline("BOXREND",
shared_ptr<TypeRecipient<SimplePool<KinectFrame>::PooledPtr>>(&br));
pp.addRecipientToNamedPipeline("BOXREND", &depthCSChan);
depthCSChan.addRecipient(&depthCSIW);
*/