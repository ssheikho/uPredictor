#include "CloudRenderer.h"
#include "CameraViewportManager.h"
#include "Point3DRGB.h"

#ifdef _WIN32
#include <opencv2/imgproc.hpp>
#elif __linux__
#include <opencv2/imgproc/imgproc.hpp>
#endif

#include <GL/glu.h>

CloudRenderer::CloudRenderer(size_t maxPts, int ptSize, GLubyte alpha
	, int imgChannelSrc, int imgChannel) :
	_maxPts(maxPts)
	, _nPts(0)
	, _ptSize(ptSize)

	, _imgChannelSrc(imgChannelSrc)
	, _imgChannel(imgChannel)

	, _alpha(alpha)
	, _cameraSpacePoints(new CameraSpacePoint[_maxPts])
	//, _colorSpacePoints(new ColorSpacePoint[_maxPts])
	//, _colorIsGood(new bool[_maxPts])
	, _rgbx(cv::Mat(1, maxPts, CV_8UC3))
	//, _bgr(new unsigned char[_maxPts * 3])
{

	#ifdef _WIN32
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
	#endif


	glGenBuffers(1, &_pointBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _pointBuffer);
	glBufferData(GL_ARRAY_BUFFER, _maxPts*sizeof(CameraSpacePoint), NULL
		, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &_colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, _maxPts * 3, NULL, GL_DYNAMIC_DRAW);

	//glBufferSubData(GL_ARRAY_BUFFER, 0, _nPts*3*sizeof(float)
	//	, _cameraSpacePoints);
}

CloudRenderer::~CloudRenderer() {
	delete[] _cameraSpacePoints;
	//delete[] _colorSpacePoints;
	//delete[] _colorIsGood;
	
	glDeleteBuffers(1, &_pointBuffer);
	glDeleteBuffers(1, &_colorBuffer);

	//delete[] _bgr;
	#ifdef _WIN32
		//ReleaseMutex(_mutex);
		CloseHandle(_mutex);
	#elif __linux__
		//pthread_mutex_unlock(&_mutex);
		pthread_mutex_destroy(&_mutex);
	#endif
}

void CloudRenderer::initializeRenderer() {}

void CloudRenderer::render(CameraViewportManager *cvm) {
	pthread_mutex_lock(&_mutex);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, _pointBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0
		, _nPts*sizeof(CameraSpacePoint)
		, _cameraSpacePoints);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0
		, _maxPts * 3
		, _rgbx.data);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, 0);

	glDrawArrays(GL_POINTS, 0, _nPts);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	pthread_mutex_unlock(&_mutex);
}

void CloudRenderer::processType(shared_ptr<Pt3DCollection> t) {
	processType(t.get());
}

void CloudRenderer::processType(Pt3DCollection *t) {
	_nPts = t->getNPts();
	if (_nPts > _maxPts) _nPts = _maxPts;

	memcpy(_cameraSpacePoints, t->getCameraPts()
		, _nPts * sizeof(CameraSpacePoint));
	memcpy(_rgbx.data, t->getRGB(), _nPts * sizeof(unsigned int));
}

void CloudRenderer::processType(SimplePool<KinectFrame>::PooledPtr t) {
	_nPts = t->_pts.getNPts();
	if (_nPts > _maxPts) _nPts = _maxPts;

	cv::Mat &rgb = t->getImageChannel(_imgChannelSrc, _imgChannel);

	memcpy(_cameraSpacePoints, t->_pts.getCameraPts()
		, _nPts * sizeof(CameraSpacePoint));
	memcpy(_rgbx.data, rgb.data, _nPts * sizeof(unsigned int));
}
