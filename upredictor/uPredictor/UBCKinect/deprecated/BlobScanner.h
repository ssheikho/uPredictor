#ifndef BLOB_SCANNER_H
#define BLOB_SCANNER_H

#include "BlobPtSet.h"

#include <opencv\cv.h>

struct FrameDesc;

class BlobScanner {
public:
	BlobScanner(FrameDesc &fd);
	~BlobScanner();

	void findBlobs(cv::Mat &a);

	cv::Mat &getMembershipImg();

protected:
	void zeroOut();
	void checkRegion(
		cv::Mat &a
		, int startX, int endX
		, int startY, int endY
		, int startBlob, int endBlob);

	cv::Mat _blobMembershipImg;

	BlobPtSet _bps;
};

#endif