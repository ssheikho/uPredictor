#ifndef KINECT_SPHERE_RENDERER_H
#define KINECT_SPHERE_RENDERER_H

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
#include "SimplePool.h"
#include "TypeRecipient.h"

//#include <Eigen/Core>
//#include <GL/GL.h>
#include <GL/gl.h>
//#include <GL/GLU.h>
#include <GL/glu.h>

//using Eigen::MatrixXd;

class SphereDescription;

class KinectSphereRenderer :
	public GLRenderInterface,
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr> {

public:
	enum {
		KSR_MODE_TRACKER_GRID
		, KSR_MODE_SPHERES
	};

	KinectSphereRenderer(int mode, int maxSpheres = 10000);
	~KinectSphereRenderer();

	void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void updateNSides(int nsides);

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

	void initializeRenderer();
	void render(CameraViewportManager *cvm);

	void addSphere(double x, double y, double z);
	void clearSpheres();
	
protected:
	int _mode, _nsides;
	GLfloat *_colorGL, *_colorGLMat;
	map<int, vector<UBCSphere>> _m;
	QuadPack _qp;
	double _r;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif
};
#endif
