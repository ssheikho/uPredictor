#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
//#include <gtk/gtk.h>
#include "CameraCalibrator.h"
#include "CloudTransformer.h"
#include "GTKShutdownInterface.h"
#include "KinectInterface.h"
#include "ShutdownContainer.h"

#include "ColumnLayout.h"
#include "AutoResizeWindow.h"
#include "KinectImageSaver.h"

//#include "CUDAColorTrackerGUI.h"
//#include "GridLayout.h"

#include "ColumnLayout.h"
#include "GLFWWindowWrapper.h"
#include "GridLayout.h"
//#include "GTKShutdownInterface.h"
#include "ImageWindow.h"
#include "IntSwitch.h"
#include "KFBGRChannel.h"
// #include "KIDepthSource.h"
#include "KinectCloudRender.h"
#include "KinectInterface.h"
#include "KinectSphereRenderer.h"
// #include "KIPointCloudSource.h"
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
	// Initialize windows.
	ShutdownContainer sc;
	GTKShutdownInterface gsi;
	sc.addChainedSI(&gsi);

	GLFWWindowWrapper window("Pt Cloud View");
	sc.addChainedSI(&window);

    cudaSetDevice(0);
    //cudaSetDevice(1);
    cudaDeviceReset();

	glewInit();
	glutInit( &argc, argv );

	gtk_init (&argc, &argv);
	//AutoResizeWindow arw(450, 145);
	AutoResizeWindow arw2(10, 10);
	AutoResizeWindow arw3(10, 10);

	//sc.addChainedSI(&arw);
	sc.addChainedSI(&arw2);
	sc.addChainedSI(&arw3);

	TrackIDManager tidm;
	KinectInterface ki(tidm, "051860134447");

	//CUDAColorSegInterface ccsi(ki.getDepthFD().w, ki.getDepthFD().h, 3);
	//ki.addRecipient(&ccsi);

	ImageWindow iw(&arw2, ki.getDepthFD().w, ki.getDepthFD().h
		, "Depth Color Image");
	KFBGRChannel chan(
		KinectFrame::KF_SOURCE_DEPTH_RGB
		, KinectFrame::KF_DEPTH_COLOR_RGB);
	KinectImageSaver kis("kinect1");
	ki.addRecipient(&kis);
	// kis.addRecipient(&chan);
	// chan.addRecipient(&iw);

/*	SimplePool<KinectFrame>::PooledPtr kf = ki.getKFPool().getInstance();
	KIDepthSource depthSource(kf, ki.getDepthFD(), ki.getDepthCM());
	KIPointCloudSource pointCloudSource(ki.getDepthCM(), &depthSource);
	CloudRenderer cr(ki.getDepthFD().w * ki.getDepthFD().h);
	pointCloudSource._pts.addRecipient(&cr);
	window.getRenderToggler().add(GLFW_KEY_O, &cr);*/
	KinectCloudRender kcr(KinectCloudRender::KR_COLOR_CLOUD_MODE
		, ki.getDepthFD().w * ki.getDepthFD().h);
	// ki.addRecipient(&kcr);
	kis.addRecipient(&kcr);
	window.getRenderToggler().add(GLFW_KEY_O, &kcr);

	//cv::Mat img1 = cv::imread("imagefolder/kinect17.jpg");
	//string imgs1[] = {"imagefolder/kinect17.jpg"};
	string imgs1[] = {
					  "imagefolder/kinect10.jpg",
					  "imagefolder/kinect11.jpg",
					  "imagefolder/kinect12.jpg",
					  "imagefolder/kinect13.jpg",
					  "imagefolder/kinect14.jpg",
					  "imagefolder/kinect15.jpg",
					  "imagefolder/kinect16.jpg",
					  "imagefolder/kinect17.jpg",
					  "imagefolder/kinect18.jpg",
					  "imagefolder/kinect19.jpg"
/*					  "imagefolder/kinect110.jpg",
					  "imagefolder/kinect111.jpg",
					  "imagefolder/kinect112.jpg",
					  "imagefolder/kinect113.jpg",
					  "imagefolder/kinect114.jpg",
					  "imagefolder/kinect115.jpg",
					  "imagefolder/kinect116.jpg",
					  "imagefolder/kinect117.jpg",
					  "imagefolder/kinect118.jpg",
					  "imagefolder/kinect119.jpg",
					  "imagefolder/kinect120.jpg",
					  "imagefolder/kinect121.jpg",
					  "imagefolder/kinect122.jpg",
					  "imagefolder/kinect123.jpg",
					  "imagefolder/kinect124.jpg",
					  "imagefolder/kinect125.jpg",
					  "imagefolder/kinect126.jpg",
					  "imagefolder/kinect127.jpg",
					  "imagefolder/kinect128.jpg",
					  "imagefolder/kinect129.jpg"*/
					};
	CameraCalibrator cc;

	//cv::Mat img2 = cv::imread("imagefolder/kinect27.jpg");
	//string imgs2[] = {"imagefolder/kinect27.jpg"};
	string imgs2[] = {
					  "imagefolder/kinect20.jpg",
					  "imagefolder/kinect21.jpg",
					  "imagefolder/kinect22.jpg",
					  "imagefolder/kinect23.jpg",
					  "imagefolder/kinect24.jpg",
					  "imagefolder/kinect25.jpg",
					  "imagefolder/kinect26.jpg",
					  "imagefolder/kinect27.jpg",
					  "imagefolder/kinect28.jpg",
					  "imagefolder/kinect29.jpg"
/*				      "imagefolder/kinect210.jpg",
					  "imagefolder/kinect211.jpg",
					  "imagefolder/kinect212.jpg",
					  "imagefolder/kinect213.jpg",
					  "imagefolder/kinect214.jpg",
					  "imagefolder/kinect215.jpg",
					  "imagefolder/kinect216.jpg",
					  "imagefolder/kinect217.jpg",
					  "imagefolder/kinect218.jpg",
					  "imagefolder/kinect219.jpg",
					  "imagefolder/kinect220.jpg",
					  "imagefolder/kinect221.jpg",
					  "imagefolder/kinect222.jpg",
					  "imagefolder/kinect223.jpg",
					  "imagefolder/kinect224.jpg",
					  "imagefolder/kinect225.jpg",
					  "imagefolder/kinect226.jpg",
					  "imagefolder/kinect227.jpg",
					  "imagefolder/kinect228.jpg",
					  "imagefolder/kinect229.jpg"*/
					};
	// int numImages = sizeof(imgs2)/sizeof(*imgs2);

	// CAM 1 -> CAM 2 NO OPTIMIZATION -----
/*	Mat image1 = imread("imagefolder/kinect10.jpg");
	Matrix4d rt1 = cc.computeHomographyForImage(image1, "051860134447");
	Mat image2 = imread("imagefolder/kinect20.jpg");
	Matrix4d rt2 = cc2.computeHomographyForImage(image2, "047404241047");
	Matrix4d nooptimizeRT = rt1 * rt2.inverse();*/
	// -----

	// TO DO 1 IMG, make sure you change NUM_VIEWS
	MatrixXd rt3 = cc.doBundleAdjustment("051860134447", imgs1, "047404241047", imgs2);

/*	cout << "[RT1]:\n" << rt1 << endl;
	cout << "[RT2]:\n" << rt2 << endl;

	MatrixXd RT = rt1 * rt2.inverse();

	cout << "[RT1 * RT2.inverse()]:\n" << RT << endl;*/

/*
	Matrix<double, 4, 1> i1, j1, k1, t1, i2, j2, k2, t2;
	i1 = rt1.col(0);
	j1 = rt1.col(1);
	k1 = rt1.col(2);
	t1 = rt1.col(3);
	i2 = rt2.col(0);
	j2 = rt2.col(1);
	k2 = rt2.col(2);
	t2 = rt2.col(3);
	Matrix<double, 3, 3> R;
	R << i2.dot(i1), j2.dot(i1), k2.dot(i1),
		 i2.dot(j1), j2.dot(j1), k2.dot(j1),
		 i2.dot(k1), j2.dot(k1), k2.dot(k1);

		 cout << "R:\n" << R << endl;
	Matrix<double, 3, 1> t, T;
	//t << t1(0,0) + t2(0,0), t1(1,0)+t2(1,0), t1(2,0)+t2(2,0);
	T << t1(0,0), t1(1,0), t1(2,0);//R * t;
	cout << "T:\n" << T << endl;
	Matrix4d RT3;
	RT3 << R, T, 0, 0, 0, 1;
	cout << "RT3:\n" << RT3 << endl;*/

	// DECOMPOSED RT1 * RT2.inverse() ........ ----------
/*	Matrix3d R14, R24;
	R14 << rt1(0,0), rt1(0,1), rt1(0,2),
			rt1(1,0), rt1(1,1), rt1(1,2),
			rt1(2,0), rt1(2,1), rt1(2,2);
				cout << "[R14]\n" << R14 << endl;
	R24 << rt2(0,0), rt2(0,1), rt2(0,2),
			rt2(1,0), rt2(1,1), rt2(1,2),
			rt2(2,0), rt2(2,1), rt2(2,2);
				cout << "[R24]\n" << R24 << endl;
	//Matrix3d R4 = R14.transpose() * R24;
	Matrix3d R4 = R14 * R24.inverse();
	Matrix<double, 3, 1> t1, t2, R4t2, T;
	t2 << rt2(0,3), rt2(1,3), rt2(2,3);
	R4t2 = R4 * t2;
	cout << "[t2]:\n" << t2 << endl;
	cout << "[R4t2]:\n" << R4t2 << endl;
	t1 << rt1(0,3), rt1(1,3), rt1(2,3);
	//t = rt2.col(3) - rt1.col(3);
	//ttemp << t(0,0), t(1,0), t(2,0);
	//T = R14.inverse() * ttemp;
	cout << "[t1]:\n" << t1 << endl;
	T = t1 - R4t2;
			cout << "[t1 - R4t2]\n" << T << endl;
	Matrix4d RT4;
	RT4 << R4, T, 0, 0, 0, 1;
	cout << "[RT4]\n" << RT4 << endl;*/
	// ---------------------------------------------------

	// CloudTransformer ct(nooptimizeRT);
	CloudTransformer ct(rt3);

	TrackIDManager tidm2;
	KinectInterface ki2(tidm2, "047404241047");

	ImageWindow iw2(&arw3, ki2.getDepthFD().w, ki2.getDepthFD().h
		, "Depth Color Image2");
	KFBGRChannel chan2(
		KinectFrame::KF_SOURCE_DEPTH_RGB
		, KinectFrame::KF_DEPTH_COLOR_RGB);
	KinectImageSaver kis2("kinect2");
	ki2.addRecipient(&kis2);
	// kis2.addRecipient(&chan2);
	// chan2.addRecipient(&iw2);


/*	SimplePool<KinectFrame>::PooledPtr kf2 = ki2.getKFPool().getInstance();
	KIDepthSource depthSource2(kf2, ki2.getDepthFD(), ki2.getDepthCM());
	KIPointCloudSource pointCloudSource2(ki2.getDepthCM(), &depthSource2);
	CloudRenderer cr2(ki2.getDepthFD().w * ki2.getDepthFD().h);
	pointCloudSource2._pts.addRecipient(&cr2);
	window.getRenderToggler().add(GLFW_KEY_P, &cr2);*/
	KinectCloudRender kcr2(KinectCloudRender::KR_COLOR_CLOUD_MODE
		, ki2.getDepthFD().w * ki2.getDepthFD().h);
	// ki2.addRecipient(&kcr2);
	// ki2.addRecipient(&ct);
	kis2.addRecipient(&ct);
	//ct.addRecipient(&cr2);
	ct.addRecipient(&kcr2);
	window.getRenderToggler().add(GLFW_KEY_P, &kcr2);

	sc.startup();
	ki.start();
	ki2.start();

	//COLLISION CLOUD

	//gtk_widget_show_all(arw.getWidget());
	gtk_widget_show_all(arw2.getWidget());
	gtk_widget_show_all(arw3.getWidget());
	//gtk_main();

	window.initializeRenderObjects();
	while (sc.isRunning()) {
		window.render();
		if (kis2.hasFrame())
			imshow("Frame", kis2.getFrame());
/*		char c = waitKey(2);
		if (c == 's')
		{
			kis.saveNextImage();
			kis2.saveNextImage();
		}*/
/*		if (kis.hasGoodFrame() && kis2.hasGoodFrame())
		{
			kis.saveImage();
			kis2.saveImage();
		}
		else
		{
			kis.resetFound();
			kis2.resetFound();
		}*/
		gtk_main_iteration();
	}

	return 0;
}
