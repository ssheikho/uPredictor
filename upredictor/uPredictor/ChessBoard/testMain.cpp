#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
//#include <gtk/gtk.h>
#include "CameraCalibrator.h"
#include "GTKShutdownInterface.h"
#include "KinectInterface.h"
#include "ShutdownContainer.h"

#include "ColumnLayout.h"
#include "AutoResizeWindow.h"

//#include "CUDAColorTrackerGUI.h"
//#include "GridLayout.h"

#include "ColumnLayout.h"
#include "GLFWWindowWrapper.h"
#include "GridLayout.h"
//#include "GTKShutdownInterface.h"
#include "ImageWindow.h"
#include "IntSwitch.h"
#include "KFBGRChannel.h"
#include "KIDepthSource.h"
#include "KinectCloudRender.h"
#include "KinectInterface.h"
#include "KinectSphereRenderer.h"
#include "KIPointCloudSource.h"
#include "PauseUnpauseUI.h"
#include "RenderToggler.h"
#include "RowLayout.h"
#include "ShutdownContainer.h"
#include "SimpleComboBox.h"

#include <cuda_gl_interop.h>
#include "cuda_runtime.h"

using namespace std;
using namespace cv; 

int main(int argc, char **argv)
{	
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
	AutoResizeWindow arw(450, 145);
	AutoResizeWindow arw2(10, 10);

	sc.addChainedSI(&arw);
	sc.addChainedSI(&arw2);

	TrackIDManager tidm;
	KinectInterface ki(tidm, "047404241047");

	KinectCloudRender kcr(KinectCloudRender::KR_COLOR_CLOUD_MODE, ki.getDepthFD().w * ki.getDepthFD().h);
	ki.addRecipient(&kcr);
	window.getRenderToggler().add(GLFW_KEY_O, &kcr);

	KinectSphereRenderer ksr(KinectSphereRenderer::KSR_MODE_SPHERES);
	ksr.setColor(255, 255, 255, 0.25);
	CameraCalibrator some(&ksr, "047404241047");
	ki.addRecipient(&some);
	window.getRenderToggler().add(GLFW_KEY_P, &ksr);

	Size imgSize(1920, 1080);
	Size boardSize(7, 9);

	sc.startup();
	ki.start();

	// gtk_widget_show_all(arw.getWidget());
	gtk_widget_show_all(arw2.getWidget());

	window.initializeRenderObjects();
	while (sc.isRunning()) {
		window.render();
		gtk_main_iteration();
		// cout << "PERIOD\n";
	}

	cout << "SUCCESSFUL BREAK!\n";	

	return 0;
}
