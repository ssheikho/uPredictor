#include "SphereRenderer.h"
#include "CameraViewportManager.h"
#include "UBCRectangularPrism.h"

#include <GL/glut.h>

SphereRenderer::SphereRenderer(UBCSphere &s) :
	_s(s)
	, _nsides(36)
	, _colorGL(new GLfloat[4])
	, _prismCache(&_ubcpf) {
	setColor(0.0, 0.0, 1.0, 0.25);

	#ifdef _WIN32
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
	#endif

	_transformationMatrixGL[0] = 1.0;
	_transformationMatrixGL[1] = 0.0;
	_transformationMatrixGL[2] = 0.0;
	_transformationMatrixGL[3] = 0.0;

	_transformationMatrixGL[4] = 0.0;
	_transformationMatrixGL[5] = 1.0;
	_transformationMatrixGL[6] = 0.0;
	_transformationMatrixGL[7] = 0.0;

	_transformationMatrixGL[8] = 0.0;
	_transformationMatrixGL[9] = 0.0;
	_transformationMatrixGL[10] = 1.0;
	_transformationMatrixGL[11] = 0.0;

	_transformationMatrixGL[12] = 0.0;
	_transformationMatrixGL[13] = 0.0;
	_transformationMatrixGL[14] = 0.0;
	_transformationMatrixGL[15] = 1.0;
}

SphereRenderer::~SphereRenderer() {
	delete[] _colorGL;
}

void SphereRenderer::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	_colorGL[0] = r;
	_colorGL[1] = g;
	_colorGL[2] = b;
	_colorGL[3] = a;
}

void SphereRenderer::updateNSides(int nsides) {
	_nsides = nsides;
}

void SphereRenderer::render(CameraViewportManager *cvm) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	UBCRectangularPrism *p = _prismCache.get(0);
	p->update(_s._x, _s._y, _s._z, _s._r);
	p->setColor(_colorGL);
	p->render(cvm);

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

/*
GLdouble transformationMatrixGL[16];

glColor4fv(_colorGL);
glPushMatrix();

_transformationMatrixGL[3] = _s._x._t;
_transformationMatrixGL[7] = _s._y._t;
_transformationMatrixGL[11] = _s._z._t;

//glMultMatrixd(_transformationMatrixGL);

//change origin to center
GLUquadric *quad = _qp.getQuad(0);	//gluNewQuadric();
glLoadIdentity();
//glMultMatrixd(_transformationMatrixGL);
cvm->sceneStep();
glTranslatef(_s._x._t, _s._y._t, _s._z._t);

//glutSolidSphere(_s._r._t, 10, 10);

gluSphere(quad, _s._r._t, _nsides, 10);
glPopMatrix();*/
