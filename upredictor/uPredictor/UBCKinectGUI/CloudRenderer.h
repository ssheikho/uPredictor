#ifndef CLOUD_RENDERER_H
#define CLOUD_RENDERER_H

#include "GLRenderInterface.h"
#include "KinectFrame.h"
#include "Pt3DCollection.h"
#include "TypeRecipient.h"

#include <opencv/cv.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <pthread.h>

#include <memory>

using namespace std;

struct Point3DRGB;

class CloudRenderer :
	public GLRenderInterface
	, public TypeRecipient<shared_ptr<Pt3DCollection>>
	, public TypeRecipient<Pt3DCollection *>
	, public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	CloudRenderer(size_t maxPts, int ptSize = 5, GLubyte alpha = 255
		, int imgChannelSrc = -1, int imgChannel = -1);
	~CloudRenderer();

	//GLRenderInterface
	void initializeRenderer();
	void render(CameraViewportManager *cvm);

	//TypeRecipient<Point3DRGB *>
	void processType(shared_ptr<Pt3DCollection> t);
	void processType(Pt3DCollection *t);
	void processType(SimplePool<KinectFrame>::PooledPtr t);

protected:
	size_t _maxPts, _nPts, _imgChannelSrc, _imgChannel;
	int _ptSize;
	GLubyte _alpha;
	CameraSpacePoint *_cameraSpacePoints;
	//ColorSpacePoint *_colorSpacePoints;
	//bool *_colorIsGood;
	//unsigned char *_bgr;
	cv::Mat _rgbx;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif

	GLuint _pointBuffer, _colorBuffer;
};

#endif
