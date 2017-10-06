#ifndef UBC_RECTANGULAR_PRISM_H
#define UBC_RECTANGULAR_PRISM_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>
#elif __linux__
#include <pthread.h>
#endif

#include "GLRenderInterface.h"
#include "string.h"

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

class RegisteredBB;

class UBCRectangularPrism :
	public GLRenderInterface {
public:
	UBCRectangularPrism();
	~UBCRectangularPrism();

	void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setColor(GLfloat *colorGL);

	void update(
		double minX3D, double maxX3D,
		double minY3D, double maxY3D,
		double minZ3D, double maxZ3D);

	void update(double x, double y, double z, double halfSide);

	//public GLRenderInterface
	void initializeRenderer();
	void render(CameraViewportManager *cvm);

protected:
	GLfloat *_colorGL;
	double _minX3D, _maxX3D, _minY3D, _maxY3D, _minZ3D, _maxZ3D;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif
};

#endif
