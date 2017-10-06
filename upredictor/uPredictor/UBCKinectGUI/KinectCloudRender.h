#ifndef KINECT_CLOUD_RENDER_H
#define KINECT_CLOUD_RENDER_H

#include "Allocator.h"
#include "CloudRenderer.h"
#include "GLRenderInterface.h"
#include "KinectFrame.h"
#include "KinectInterface.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

#include <opencv2/core/core.hpp>

#include <queue>

class Pt3DCollection;
class RecordingFrameBuffer;

class KinectCloudRender :
	public CloudRenderer
{
public:
	enum KR_MODE {
		KR_COLOR_CLOUD_MODE
		, KR_SEGMENT_CLOUD_MODE
		//, KR_INLIER_CLOUD_MODE
		, KR_MODE_COUNT
	};

	//Pt3DCollection *pts
	KinectCloudRender(KR_MODE mode
		//, UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc
		, size_t maxPts, int ptSize = 5, GLubyte alpha = 255);
	~KinectCloudRender();
	
	//TypeRecipient
	void processType(SimplePool<KinectFrame>::PooledPtr kf);
	void onStartup();

	/*
	//GLRenderInterface
	void render();
	*/

protected:
	//SimplePool<KinectFrame>::PooledPtr _kf;

	KR_MODE _mode;
	//Pt3DCollection *_pts;
};

#endif
