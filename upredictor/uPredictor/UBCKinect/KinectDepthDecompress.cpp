#include "KinectDepthDecompress.h"
#include "FrameDesc.h"

//#include <opencv2/highgui.hpp>

KinectDepthDecompress::KinectDepthDecompress() :
	_fi(NULL)
	, _imgSize(0)
	, _maxSizeComp(0)
	, _buf(NULL) {
	LZ4F_createDecompressionContext(&_dCtx, LZ4F_VERSION);
}

#ifdef _WIN32
KinectDepthDecompress::KinectDepthDecompress(wstring fileName, FrameDesc &fd) :
#elif __linux__
KinectDepthDecompress::KinectDepthDecompress(string fileName, FrameDesc &fd) :
#endif
	_fi(NULL)
	, _imgSize(0)
	, _maxSizeComp(0)
	, _buf(NULL) {
	LZ4F_createDecompressionContext(&_dCtx, LZ4F_VERSION);
	open(fileName, fd);
}

KinectDepthDecompress::~KinectDepthDecompress() {
	close();
	LZ4F_freeDecompressionContext(_dCtx);
}

#ifdef _WIN32
bool KinectDepthDecompress::open(wstring fileName, FrameDesc &fd) {
#elif __linux__
bool KinectDepthDecompress::open(string fileName, FrameDesc &fd) {
#endif
	bool retVal = !_fi;
	if (retVal) {
		_fi = new FileIndex(fileName, 100000, true);
		_imgSize = fd.w * fd.h * fd.bpp;
		_maxSizeComp = LZ4F_compressFrameBound(_imgSize, NULL);
		_buf = new char[_maxSizeComp];
	}
	return retVal;
}

void KinectDepthDecompress::close() {
	if (_fi) {
		_fi->finalize();
		delete _fi;
		delete[] _buf;
	}
}

void KinectDepthDecompress::fillInFrame(
	SimplePool<KinectFrame>::PooledPtr t, long index) {
	if (_fi) {
		size_t size = _fi->read(index, (unsigned char *)_buf, _maxSizeComp);
		size_t decompBufSize = _imgSize;

		size_t decompSize = LZ4F_decompress(_dCtx, t->_depth.data,
			&decompBufSize, _buf, &size, NULL);
	}
}

long KinectDepthDecompress::getNFrames() {
	return _fi == NULL ? 0 : _fi->getNRecs();
}
