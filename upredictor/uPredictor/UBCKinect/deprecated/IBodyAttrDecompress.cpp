#include "IBodyAttrDecompress.h"
#include "IBodyAttrs.h"

IBodyAttrDecompress::IBodyAttrDecompress() :
	_maxSizeComp(LZ4F_compressFrameBound(sizeof(IBodyAttrs), NULL))
	//, _compressedSize(0)
	//, _buf(new char[_maxSizeComp])
{
	LZ4F_createDecompressionContext(&_cCtx, LZ4F_VERSION);
}

IBodyAttrDecompress::~IBodyAttrDecompress() {
	LZ4F_freeDecompressionContext(_cCtx);
}

size_t IBodyAttrDecompress::getMaxCompressedSize() {
	return _maxSizeComp;
}

size_t IBodyAttrDecompress::processIBodyAttrs(
	IBodyAttrs *attrs
	, char *buf
	, size_t size) {
	size_t decompBufSize = sizeof(IBodyAttrs);
	return LZ4F_decompress(_cCtx, attrs, &decompBufSize, attrs, &size, NULL);
}

/*
char *IBodyAttrCompress::getCompressedBuf() {
return _buf;
}

size_t IBodyAttrCompress::getCompressedSize() {
return _compressedSize;
}
*/