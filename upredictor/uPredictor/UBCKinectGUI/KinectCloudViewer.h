#ifndef KINECT_CLOUD_VIEWER_H
#define KINECT_CLOUD_VIEWER_H

#include "KinectFrame.h"
#include "ShutdownInterface.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

//#include <pcl/visualization/cloud_viewer.h>

class KinectCloudViewer :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public ShutdownInterface
{
public:
	KinectCloudViewer(string windowTitle);
	~KinectCloudViewer();

	//TypeRecipient
	void processType(SimplePool<KinectFrame>::PooledPtr kf);

	//ShutdownInterface
	bool isRunning();

protected:
	//ShutdownInterface
	void doStartup();
	void doShutdown();

	void onStartup();
	void onShutdown();
	void onAddChained(ShutdownInterface *si);

	pcl::visualization::CloudViewer _viewer;	
	//boost::shared_ptr<pcl::visualization::PCLVisualizer> _viewer;
};

#endif