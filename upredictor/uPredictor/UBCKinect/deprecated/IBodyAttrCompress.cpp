#include "IBodyAttrCompress.h"
#include "IBodyAttrs.h"

IBodyAttrCompress::IBodyAttrCompress() :
	_maxSizeComp(LZ4F_compressFrameBound(sizeof(IBodyAttrs), NULL))
	//, _compressedSize(0)
	//, _buf(new char[_maxSizeComp])
{
	LZ4F_createCompressionContext(&_cCtx, LZ4F_VERSION);
}

IBodyAttrCompress::~IBodyAttrCompress() {
	LZ4F_freeCompressionContext(_cCtx);
}

size_t IBodyAttrCompress::getMaxCompressedSize() {
	return _maxSizeComp;
}

size_t IBodyAttrCompress::processIBodyAttrs(IBodyAttrs *attrs, char *buf) {
	return LZ4F_compressFrame(buf, _maxSizeComp, attrs, sizeof(IBodyAttrs),
		NULL);
}

/*
char *IBodyAttrCompress::getCompressedBuf() {
	return _buf;
}

size_t IBodyAttrCompress::getCompressedSize() {
	return _compressedSize;
}
*/