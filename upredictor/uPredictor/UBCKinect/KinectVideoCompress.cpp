#include "KinectVideoCompress.h"
#include "FrameDesc.h"
#include "UBCUtil.h"

//#include <exception>

//Upgrade to CudaCodec
KinectVideoCompress::KinectVideoCompress() : _vw(NULL) {
	#ifdef _WIN32
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		pthread_mutex_init(&_mutex, NULL);
	#endif
}

#ifdef _WIN32
KinectVideoCompress::KinectVideoCompress(wstring fileName, FrameDesc &fd) :
	_vw(NULL) {
	_mutex = CreateMutex(NULL, FALSE, NULL);
#elif __linux__
KinectVideoCompress::KinectVideoCompress(string fileName, FrameDesc &fd) :
	_vw(NULL) {
	pthread_mutex_init(&_mutex, NULL);
#endif
	open(fileName, fd);
}

KinectVideoCompress::~KinectVideoCompress() {
	close();
}

#ifdef _WIN32
bool KinectVideoCompress::open(wstring fileName, FrameDesc &fd) {
	WaitForSingleObject(_mutex, INFINITE);
#elif __linux__
bool KinectVideoCompress::open(string fileName, FrameDesc &fd) {
	pthread_mutex_lock(&_mutex);
#endif
	bool retVal = !_vw;
	if (retVal) {
		//int fourcc = -1;
		int fourcc = CV_FOURCC('X', '2', '6', '4');
		_vw =
			new cv::VideoWriter(
			#ifdef _WIN32
				wstringToString(fileName)
			#elif __linux__
				fileName
			#endif
				, fourcc, 30.0, cvSize(fd.w, fd.h), true);
	}

	if (!_vw->isOpened()) {
		delete _vw;
		_vw = NULL;
	}

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
	return retVal;
}

void KinectVideoCompress::close() {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif
	if (_vw) {
		_vw->release();
		delete _vw;
		_vw = NULL;
	}
	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void KinectVideoCompress::processType(SimplePool<KinectFrame>::PooledPtr t) {
	//_vw.write(t->_bgr);

	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	if (_vw) {
		//try {
			_vw->write(t->_bgra);
			//_vw->write(t->_yuy);
		//}
		//catch (std::Exception e) {
		//	e = e;
		//}
	}

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}
