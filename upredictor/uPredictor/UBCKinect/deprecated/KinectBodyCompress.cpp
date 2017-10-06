#include "KinectBodyCompress.h"

#include <opencv2/highgui.hpp>

KinectBodyCompress::KinectBodyCompress() :
	_fi(NULL)
	, _curBufSize(0)
	, _maxBufSize(0)
	, _buf(NULL) {
	//LZ4F_createCompressionContext(&_cCtx, LZ4F_VERSION);
}

KinectBodyCompress::KinectBodyCompress(wstring fileName, int nBodies) :
	_fi(NULL)
	, _curBufSize(0)
	, _maxBufSize(0)
	, _buf(NULL) {
	//LZ4F_createCompressionContext(&_cCtx, LZ4F_VERSION);
	open(fileName, nBodies);
}

KinectBodyCompress::~KinectBodyCompress() {
	close();
	//LZ4F_freeCompressionContext(_cCtx);
}

bool KinectBodyCompress::open(wstring fileName, int nBodies) {
	bool retVal = !_fi;
	if (retVal) {
		_fi = new FileIndex(fileName, 100000, false);
		_maxBufSize = 
			sizeof(size_t) +
			((sizeof(size_t) + _comp.getMaxCompressedSize()) * nBodies)
			;
		_buf = new char[_maxBufSize];
	}
	return retVal;
}

void KinectBodyCompress::close() {
	if (_fi) {
		_fi->finalize();
		delete _fi;
		delete[] _buf;
	}
}

void KinectBodyCompress::processType(SimplePool<KinectFrame>::PooledPtr t) {
	if (_fi) {
		size_t nTracked = t->_bcc.getNTracked();
		
		*((size_t *)_buf) = nTracked;
		_curBufSize = sizeof(size_t);

		for (size_t i = 0; i < nTracked; i++) {
			size_t s =
				_comp.processIBodyAttrs(
					&t->_bcc.getBC(i)->getIBA()
					, &_buf[_curBufSize + sizeof(size_t)]);
			*((size_t*)&_buf[_curBufSize]) = s;
			_curBufSize += sizeof(size_t) + s;
		}
	}
}