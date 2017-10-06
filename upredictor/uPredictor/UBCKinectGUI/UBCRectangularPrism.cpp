#include "UBCRectangularPrism.h"

UBCRectangularPrism::UBCRectangularPrism() :
	_colorGL(new GLfloat[4])
{
	setColor(0.0, 0.0, 1.0, 0.25);
	
	#ifdef _WIN32
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
	#endif
}

UBCRectangularPrism::~UBCRectangularPrism() {}

void UBCRectangularPrism::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	_colorGL[0] = r;
	_colorGL[1] = g;
	_colorGL[2] = b;
	_colorGL[3] = a;
}

void UBCRectangularPrism::setColor(GLfloat *colorGL) {
	memcpy(_colorGL, colorGL, 4 * sizeof(GLfloat));
}

void UBCRectangularPrism::update(
	double minX3D, double maxX3D,
	double minY3D, double maxY3D,
	double minZ3D, double maxZ3D) {
	
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	_minX3D = minX3D;	_maxX3D = maxX3D;
	_minY3D = minY3D;	_maxY3D = maxY3D;
	_minZ3D = minZ3D;	_maxZ3D = maxZ3D;

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void UBCRectangularPrism::update(double x, double y, double z, double halfSide) {
	update(
		x - halfSide, x + halfSide,
		y - halfSide, y + halfSide,
		z - halfSide, z + halfSide);
}

void UBCRectangularPrism::initializeRenderer() {}

void UBCRectangularPrism::render(CameraViewportManager *cvm) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	glColor4fv(_colorGL);

	//TOP
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(_minX3D, _maxY3D, _minZ3D);
	glVertex3f(_minX3D, _maxY3D, _maxZ3D);
	glVertex3f(_maxX3D, _maxY3D, _maxZ3D);
	glVertex3f(_maxX3D, _maxY3D, _minZ3D);
	glEnd();

	//BOTTOM
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(_minX3D, _minY3D, _minZ3D);
	glVertex3f(_minX3D, _minY3D, _maxZ3D);
	glVertex3f(_maxX3D, _minY3D, _maxZ3D);
	glVertex3f(_maxX3D, _minY3D, _minZ3D);
	glEnd();

	//FRONT
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(_minX3D, _minY3D, _minZ3D);
	glVertex3f(_minX3D, _maxY3D, _minZ3D);
	glVertex3f(_maxX3D, _maxY3D, _minZ3D);
	glVertex3f(_maxX3D, _minY3D, _minZ3D);
	glEnd();

	//BACK
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(_minX3D, _minY3D, _maxZ3D);
	glVertex3f(_minX3D, _maxY3D, _maxZ3D);
	glVertex3f(_maxX3D, _maxY3D, _maxZ3D);
	glVertex3f(_maxX3D, _minY3D, _maxZ3D);
	glEnd();

	//LEFT
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(_minX3D, _minY3D, _minZ3D);
	glVertex3f(_minX3D, _minY3D, _maxZ3D);
	glVertex3f(_minX3D, _maxY3D, _maxZ3D);
	glVertex3f(_minX3D, _maxY3D, _minZ3D);
	glEnd();

	//RIGHT
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(_maxX3D, _minY3D, _minZ3D);
	glVertex3f(_maxX3D, _minY3D, _maxZ3D);
	glVertex3f(_maxX3D, _maxY3D, _maxZ3D);
	glVertex3f(_maxX3D, _maxY3D, _minZ3D);
	glEnd();


	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}
