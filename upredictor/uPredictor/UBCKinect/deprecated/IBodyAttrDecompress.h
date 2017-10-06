#ifndef I_BODY_ATTR_DECOMPRESS_H
#define I_BODY_ATTR_DECOMPRESS_H

#include <lz4frame_static.h>

#include <string>

using namespace std;

struct FrameDesc;
struct IBodyAttrs;

class IBodyAttrDecompress {
public:
	IBodyAttrDecompress();
	~IBodyAttrDecompress();

	size_t getMaxCompressedSize();

	size_t processIBodyAttrs(
		IBodyAttrs *attrs
		, char *buf
		, size_t size);
	//char *getCompressedBuf();
	//size_t getCompressedSize();

protected:
	size_t _maxSizeComp;// , _compressedSize;
						//char *_buf;
	LZ4F_decompressionContext_t _cCtx;
};

#endif