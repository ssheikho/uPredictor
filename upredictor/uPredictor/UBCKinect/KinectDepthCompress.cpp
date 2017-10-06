#include "KinectDepthCompress.h"
#include "FrameDesc.h"

//#include <opencv2/highgui.hpp>

KinectDepthCompress::KinectDepthCompress() :
	_fi(NULL)
,	_imgSize(0)
,	_maxSizeComp(0)
,	_buf(NULL) {
	LZ4F_createCompressionContext(&_cCtx, LZ4F_VERSION);
}

#ifdef _WIN32
KinectDepthCompress::KinectDepthCompress(wstring fileName, FrameDesc &fd) :
#elif __linux__
KinectDepthCompress::KinectDepthCompress(string fileName, FrameDesc &fd) :
#endif
	_fi(NULL)
	, _imgSize(0)
	, _maxSizeComp(0)
	, _buf(NULL) {
	LZ4F_createCompressionContext(&_cCtx, LZ4F_VERSION);
	open(fileName, fd);
}

KinectDepthCompress::~KinectDepthCompress() {
	close();
	LZ4F_freeCompressionContext(_cCtx);
}

#ifdef _WIN32
bool KinectDepthCompress::open(wstring fileName, FrameDesc &fd) {
#elif __linux__
bool KinectDepthCompress::open(string fileName, FrameDesc &fd) {
#endif
	bool retVal = !_fi;
	if (retVal) {
		_fi = new FileIndex(fileName, 100000, false);
		_imgSize = fd.w * fd.h * fd.bpp;
		_maxSizeComp = LZ4F_compressFrameBound(_imgSize, NULL);
		_buf = new char[_maxSizeComp];
	}
	return retVal;
}

void KinectDepthCompress::close() {
	if (_fi) {
		_fi->finalize();
		delete _fi;
		delete[] _buf;
	}
}

void KinectDepthCompress::processType(SimplePool<KinectFrame>::PooledPtr t) {
	if (_fi) {
		size_t size = LZ4F_compressFrame(_buf, _maxSizeComp, t->_depth.data,
			_imgSize, NULL);
		_fi->write((unsigned char *)_buf, size);
	}
}

void KinectDepthCompress::onStartup() {};
