#include "KinectBodyDecompress.h"

#include <opencv2/highgui.hpp>

KinectBodyDecompress::KinectBodyDecompress() :
	_fi(NULL)
	, _maxBufSize(0)
	, _buf(NULL) {}

KinectBodyDecompress::KinectBodyDecompress(wstring fileName, int nBodies) :
	_fi(NULL)
	, _maxBufSize(0)
	, _buf(NULL) {
	open(fileName, nBodies);
}

KinectBodyDecompress::~KinectBodyDecompress() {
	close();
}

bool KinectBodyDecompress::open(wstring fileName, int nBodies) {
	bool retVal = !_fi;
	if (retVal) {
		_fi = new FileIndex(fileName, 100000, true);
		_maxBufSize =
			sizeof(size_t) +
			((sizeof(size_t) + _comp.getMaxCompressedSize()) * nBodies)
			;
		_buf = new char[_maxBufSize];
	}
	return retVal;
}

void KinectBodyDecompress::close() {
	if (_fi) {
		_fi->finalize();
		delete _fi;
		delete[] _buf;
	}
}

void KinectBodyDecompress::fillInFrame(
	SimplePool<KinectFrame>::PooledPtr t
	, long index)
{
	if (_fi) {
		size_t size = _fi->read(index, (unsigned char *)_buf, _maxBufSize);

		size_t nTracked = *(size_t*)_buf;
		size_t curBufSize = sizeof(size_t);

		for (size_t i = 0; i < nTracked; i++) {
			size_t compressedBodySize = *(size_t*)&_buf[curBufSize];
			curBufSize += sizeof(size_t);

			size_t s =
				_comp.processIBodyAttrs(
					&t->_bcc.getBC(i)->getIBA()
					, &_buf[curBufSize]
					, compressedBodySize
					);

			curBufSize += s;
		}
	}
}

long KinectBodyDecompress::getNFrames() {
	return _fi ? _fi->getNRecs() : 0;
}