#ifndef KINECT_CLOUD_RENDER_H
#define KINECT_CLOUD_RENDER_H

#include "GLRenderInterface.h"
#include "KinectImageFrameRecipient.h"
#include "KinectInterface.h"

#include <opencv2/core/core.hpp>

class Pt3DCollection;
class RecordingFrameBuffer;

class KinectCloudRender :
	//public KinectDataRecipient,
	public KinectImageFrameRecipient
	, public GLRenderInterface
{
public:
	//Pt3DCollection *pts
	KinectCloudRender();
	~KinectCloudRender();

	//void update(RecordingFrame *rf);

	//KinectImageFrameRecipient
	void processKinectImageFrame(KinectImageFrame *kif);

	//GLRenderInterface
	void render();

protected:
	KinectImageFrame *_kif;
	//Pt3DCollection *_pts;
};

#endif