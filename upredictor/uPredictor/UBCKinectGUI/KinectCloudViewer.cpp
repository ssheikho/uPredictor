#include "KinectCloudViewer.h"

//http://pointclouds.org/documentation/tutorials/pcl_visualizer.php

KinectCloudViewer::KinectCloudViewer(string windowTitle) :
	_viewer(windowTitle)
	//_viewer(new pcl::visualization::PCLVisualizer("3D Viewer"))
{
	/*
	_viewer->setBackgroundColor(0, 0, 0);
	_viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
	_viewer->addCoordinateSystem(1.0);
	_viewer->initCameraParameters();
	*/
	/*
	_viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
	_viewer->addCoordinateSystem(1.0);
	_viewer->initCameraParameters();
	*/
}

KinectCloudViewer::~KinectCloudViewer() {}

//TypeRecipient
void KinectCloudViewer::processType(SimplePool<KinectFrame>::PooledPtr kf) {
	//pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB>
	//	rgb(kf->_reg.getCloudRGB());
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB>
	//	single_color(kf->_reg.getCloudRGB(), 0, 255, 0);
	//_viewer->addPointCloud<pcl::PointXYZRGB>(kf->_reg.getCloudRGB()
	//	, single_color, "sample cloud");

	//_viewer.showCloud(kf->_reg.getCloudRGBA());
	//boost::shared_ptr<pcl::visualization::PCLVisualizer>rgbVis(kf->_reg.getCloud())
	//_viewer->addPointCloud<pcl::PointXYZRGB>(kf->_reg.getCloud()
	//	, rgb, "sample cloud");
}

bool KinectCloudViewer::isRunning() {
	return true;// !_viewer->wasStopped();
}

void KinectCloudViewer::doStartup() {}
void KinectCloudViewer::doShutdown() {}

void KinectCloudViewer::onStartup() {}
void KinectCloudViewer::onShutdown() {}
void KinectCloudViewer::onAddChained(ShutdownInterface *si) {}