#include "KinectQuiverRenderer.h"

KinectQuiverRenderer::KinectQuiverRenderer(
	size_t maxPts
	, ValueListener<double> &quiverLen
	, int ptSize, GLubyte alpha) :
	_maxPts(maxPts)
	, _nPts(0)
	, _quiverLen(quiverLen)
	, _ptSize(ptSize)
	, _alpha(alpha)
	, _cameraSpacePoints(new CameraSpacePoint[_maxPts])
	//, _colorSpacePoints(new ColorSpacePoint[_maxPts])
	, _colorIsGood(new bool[_maxPts])
	, _bgr(new unsigned char[_maxPts * 3])
	, _normVectsX(new float[_maxPts * 3]), _normVectsY(new float[_maxPts * 3])
	, _normsX(new float[_maxPts]), _normsY(new float[_maxPts])
{
	#ifdef _WIN32	
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
	#endif
}

KinectQuiverRenderer::~KinectQuiverRenderer() {
	delete[] _normVectsX;
	delete[] _normVectsY;
	delete[] _normsX;
	delete[] _normsY;
}

void KinectQuiverRenderer::render(CameraViewportManager *cvm) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	glPushMatrix();
	//glBegin(GL_POINTS);
	//glPointSize(_ptSize);
	for (int i = 0; i < _nPts; i++) {
		if (_colorIsGood[i]) {
			int colorIndex = 3 * i;

			glBegin(GL_LINES);

			glColor4ub(_bgr[colorIndex + 2], _bgr[colorIndex + 1]
				, _bgr[colorIndex], _alpha);

			glVertex3f(
				_cameraSpacePoints[i].X, _cameraSpacePoints[i].Y
				, _cameraSpacePoints[i].Z);
			glVertex3f(
				_cameraSpacePoints[i].X +
				_normVectsX[colorIndex] * _normsX[i]
				, _cameraSpacePoints[i].Y +
				_normVectsX[colorIndex + 1] * _normsX[i]
				, _cameraSpacePoints[i].Z +
				_normVectsX[colorIndex + 2] * _normsX[i]);
			glEnd();

			glBegin(GL_LINES);

			glColor4ub(_bgr[colorIndex + 2], _bgr[colorIndex + 1]
				, _bgr[colorIndex], _alpha);

			glVertex3f(
				_cameraSpacePoints[i].X, _cameraSpacePoints[i].Y
				, _cameraSpacePoints[i].Z);
			glVertex3f(
				_cameraSpacePoints[i].X +
				_normVectsY[colorIndex] * _normsY[i]
				, _cameraSpacePoints[i].Y +
				_normVectsY[colorIndex + 1] * _normsY[i]
				, _cameraSpacePoints[i].Z +
				_normVectsY[colorIndex + 2] * _normsY[i]);
			glEnd();
		}
	}
	//glEnd();
	glPopMatrix();

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}


void KinectQuiverRenderer::processType(SimplePool<KinectFrame>::PooledPtr kf) {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	ArrayPt3DCollection &reg = kf->getRegisteredPts();
	_nPts = reg.getNPts();
	if (_nPts > _maxPts) _nPts = _maxPts;
	memcpy(_cameraSpacePoints, reg.getCameraPts()
		, _nPts * sizeof(CameraSpacePoint));
	//memcpy(_colorIsGood, reg.getColorIsGood()
	//	, _nPts * sizeof(bool));
	memcpy(_bgr, reg.getRGB()
		, _nPts * 3 * sizeof(unsigned char));

	/*
	memcpy(_normVectsX, kf->_normVectsX.data
		, _nPts * 3 * sizeof(float));
	memcpy(_normVectsY, kf->_normVectsY.data
		, _nPts * 3 * sizeof(float));

	memcpy(_normsX, kf->_normsX.data
		, _nPts * sizeof(float));
	memcpy(_normsY, kf->_normsY.data
		, _nPts * sizeof(float));
	*/

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void KinectQuiverRenderer::onStartup() {}
