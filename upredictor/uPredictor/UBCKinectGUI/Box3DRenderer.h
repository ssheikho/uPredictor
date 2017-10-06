#ifndef BOX_3D_RENDERER_H
#define BOX_3D_RENDERER_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>
#elif __linux__
#include <pthread.h>
#endif

#include "GLRenderInterface.h"
#include "KinectFrame.h"
#include "QuadPack.h"
#include "SimpleCache.h"
#include "SimplePool.h"
#include "TypeRecipient.h"
#include "UBCRectangularPrismFactory.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

class Box3DRenderer :
	public GLRenderInterface,
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {
public:
	enum {
		B3DR_MODE_BOXES
		, B3DR_MODE_SPHERE_BB
	};

	Box3DRenderer(int mode = B3DR_MODE_BOXES);
	~Box3DRenderer();

	void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	//public GLRenderInterface
	void initializeRenderer();
	void render(CameraViewportManager *cvm);

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

protected:
	int _mode;
	GLfloat *_colorGL;

	UBCRectangularPrismFactory _ubcpf;
	SimpleCache<UBCRectangularPrism> _prismCache;
	size_t _nBoxes;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif
};

#endif
