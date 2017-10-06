#ifndef KINECT_QUIVER_RENDERER_H
#define KINECT_QUIVER_RENDERER_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>
#elif __linux__
#include <pthread.h>
#endif

#include "GLRenderInterface.h"
#include "KinectInterface.h"
#include "SimplePool.h"
#include "TypeRecipient.h"
#include "ValueListener.h"

//#include <GL/GL.h>
#include <GL/gl.h>

class KinectQuiverRenderer :
	public GLRenderInterface
	, public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	KinectQuiverRenderer(
		size_t maxPts
		, ValueListener<double> &quiverLen
		, int ptSize = 5, GLubyte alpha = 255);
	~KinectQuiverRenderer();

	//GLRenderInterface
	void render(CameraViewportManager *cvm);

	//TypeRecipient
	void processType(SimplePool<KinectFrame>::PooledPtr kf);
	void onStartup();

protected:
	size_t _maxPts, _nPts;
	ValueListener<double> &_quiverLen;
	int _ptSize;
	GLubyte _alpha;
	CameraSpacePoint *_cameraSpacePoints;
	//ColorSpacePoint *_colorSpacePoints;
	bool *_colorIsGood;
	unsigned char *_bgr;
	float	*_normVectsX, *_normVectsY
			,*_normsX, *_normsY;

	#ifdef _WIN32	
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif
};

#endif
