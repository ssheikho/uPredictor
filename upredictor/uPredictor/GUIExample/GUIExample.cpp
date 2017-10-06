#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include <tchar.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "AutoResizeWindow.h"

#include "ColumnLayout.h"
#include "CUDAColorSegInterface.h"
#include "CUDAColorTrackerGUI.h"
#include "GLFWWindowWrapper.h"
#include "GridLayout.h"
#include "GTKShutdownInterface.h"
#include "ImageWindow.h"
#include "IntSwitch.h"
#include "KFBGRChannel.h"
#include "KIDepthSource.h"
#include "KinectCloudRender.h"
#include "KinectInterface.h"
#include "KIPointCloudSource.h"
#include "PauseUnpauseUI.h"
#include "PtSubset.h"
#include "RenderToggler.h"
#include "RowLayout.h"
#include "ShutdownContainer.h"
#include "SimpleComboBox.h"
//#include "SimpleLabeledSlider.h"

#include "SimpleLoadSave.h"
#include "SimpleLoadSaveInterface.h"
#include "TrackerSliders.h"
#include "TrackerUI.h"
#include "TypeRecipientToggler.h"
#include "UBCButton.h"
#include "UBCDARTModelRenderer.h"
#include "UBCDARTTracker.h"
#include "UBCDARTTrackerModelRenderer.h"
// #include "UBCEntry.h"

#include <mesh/assimp_mesh_reader.h>
#include <pose/pose_reduction.h>
#include <util/dart_io.h>

#include <cuda_gl_interop.h>
#include "cuda_runtime.h"

#include <cl.hpp>

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	ShutdownContainer sc;
	GTKShutdownInterface gsi;
	sc.addChainedSI(&gsi);

	GLFWWindowWrapper window("Pt Cloud View");
	sc.addChainedSI(&window);

    cudaSetDevice(0);
    cudaDeviceReset();

	glewInit();
	glutInit( &argc, argv );

	gtk_init (&argc, &argv);

	TrackIDManager tidm;
	KinectInterface ki(tidm);

	AutoResizeWindow arw2(10, 10);
	MarginalTrackerParams mtp;
	CUDAColorSegInterface ccsi(ki.getDepthFD().w, ki.getDepthFD().h, 3, mtp);
	ColumnLayout colorSegCL(&arw2, 10, 10);
	CUDAColorTrackerGUI ggtg(&colorSegCL, &mtp);
	ki.addRecipient(&ccsi);
	sc.addChainedSI(&arw2);

	ImageWindow iw(&colorSegCL, ki.getDepthFD().w, ki.getDepthFD().h
		, "Depth Color Image");
	KFBGRChannel chan(
		KinectFrame::KF_SOURCE_DEPTH_RGB
		, KinectFrame::KF_DEPTH_SEGS_RGB);
	ccsi.addRecipient(&chan);
	chan.addRecipient(&iw);

	//PtSubset ptSubset(ki.getDepthFD().w * ki.getDepthFD().h, 20
	//	, KinectFrame::KF_SOURCE_DEPTH_RGB
	//	, KinectFrame::KF_DEPTH_SEGS_RGB);
	//ccsi.addRecipient(&ptSubset);

    dart::Model::initializeRenderer(new dart::AssimpMeshReader());
	SimplePool<KinectFrame>::PooledPtr kf = ki.getKFPool().getInstance();
	KIDepthSource depthSource(kf, ki.getDepthFD(), ki.getDepthCM());
	KIPointCloudSource pointCloudSource(ki.getDepthCM(), &depthSource);
	dart::UBCDARTTracker tracker(pointCloudSource, ki.getDepthCM());
	ccsi.addRecipient(&tracker);

	float defaultModelSdfResolution = 0.005;
	float defaultModelSdfPadding = 0.07;
	int obsSdfSize = 64;
	float obsSdfResolution = 0.01*32.0/obsSdfSize;
    const static float3 obsSdfOffset = make_float3(0,0,0.1);

	tracker.addModel(
		"../Linux/Third-Party/dart/models/leftHand/leftHand.xml"
		, defaultModelSdfResolution
	);

	dart::UBCDARTTrackerModelRenderer trackerRenderer(tracker, 0);

	CloudRenderer cr(ki.getDepthFD().w * ki.getDepthFD().h);
	pointCloudSource._pts.addRecipient(&cr);
	//ptSubset.TypeBroadcaster<Pt3DCollection *>::addRecipient(&cr);

	window.getRenderToggler().add(GLFW_KEY_O, &cr);
	window.getRenderToggler().add(GLFW_KEY_P, &trackerRenderer);

	AutoResizeWindow arw3(450, 145);
	ColumnLayout arw3cl(&arw3, 450, 145);

	SimpleComboBox scb(&arw3cl);
	scb.addSelection("Tracker", 0);
	scb.addSelection("Sliders", 1);

	RowLayout trackerRL(&arw3cl, 100, 100);
	TrackerUI trackerUI(&trackerRL, tracker.getPose(0), 0);
	TrackerSliders trackerSliders(&trackerRL, tracker.getPose(0));
	TypeRecipientToggler<dart::UBCDARTTracker *> trt;
	trt.addRecipient(&trackerUI);
	trt.addRecipient(&trackerSliders);
	trt.getC().processType(1);
	tracker.addRecipient(&trt);
	
	sc.addChainedSI(&arw3);

	sc.startup();
	ki.start();

	//COLLISION CLOUD

	gtk_widget_show_all(arw2.getWidget());
	gtk_widget_show_all(arw3.getWidget());
	//gtk_main();

	window.initializeRenderObjects();
	while (sc.isRunning()) {
		window.render();
		gtk_main_iteration();
	}

    dart::Model::shutdownRenderer();

	return 0;
}
