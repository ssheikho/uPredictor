#ifndef SPHERE_RENDERER_H
#define SPHERE_RENDERER_H

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
#include "SimpleCache.h"
#include "TypeRecipient.h"
#include "UBCRectangularPrismFactory.h"

#include <Eigen/Core>
#include <GL/gl.h>
#include <GL/glu.h>

using Eigen::MatrixXd;

class SphereRenderer : public GLRenderInterface {

public:
	SphereRenderer(UBCSphere &s);
	~SphereRenderer();

	void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void updateNSides(int nsides);

protected:
	void render(CameraViewportManager *cvm);

	UBCSphere &_s;
	int _nsides;
	GLfloat *_colorGL;
	QuadPack _qp;

	UBCRectangularPrismFactory _ubcpf;
	SimpleCache<UBCRectangularPrism> _prismCache;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif

	GLdouble _transformationMatrixGL[16];
};
#endif
