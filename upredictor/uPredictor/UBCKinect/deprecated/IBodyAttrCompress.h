#ifndef I_BODY_ATTR_COMPRESS_H
#define I_BODY_ATTR_COMPRESS_H

#include <lz4frame_static.h>

#include <string>

using namespace std;

struct FrameDesc;
struct IBodyAttrs;

class IBodyAttrCompress {
public:
	IBodyAttrCompress();
	~IBodyAttrCompress();

	size_t getMaxCompressedSize();

	size_t processIBodyAttrs(IBodyAttrs *attrs, char *buf);
	//char *getCompressedBuf();
	//size_t getCompressedSize();

protected:
	size_t _maxSizeComp;// , _compressedSize;
	//char *_buf;
	LZ4F_compressionContext_t _cCtx;
};

#endif