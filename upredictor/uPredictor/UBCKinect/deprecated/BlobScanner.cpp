#include "BlobScanner.h"
#include "BlobPts.h"
#include "FrameDesc.h"

typedef unsigned char     uint8_t;

BlobScanner::BlobScanner(FrameDesc &fd) :
	_blobMembershipImg(fd.h, fd.w, CV_8UC1)
	, _bps(fd.h * fd.w)
{}

BlobScanner::~BlobScanner() {}

void BlobScanner::findBlobs(cv::Mat &a) {
	zeroOut();
	checkRegion(a, 0, a.cols, 0, a.rows, 0, 10);
}

cv::Mat &BlobScanner::getMembershipImg() {
	return _blobMembershipImg;
}

void BlobScanner::zeroOut() {
	memset(_blobMembershipImg.data, 0
		, sizeof(uint8_t) * _blobMembershipImg.rows * _blobMembershipImg.cols);
}

void BlobScanner::checkRegion(
	cv::Mat &a
	, int startX, int endX
	, int startY, int endY
	, int startBlob, int endBlob) {
	int rowStartCur = 0;
	int rowStartPrev = rowStartCur;
	BlobPts *curBlob = NULL;

	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < endX; x++) {
			if (a.data[rowStartCur + x] == 0) {
				curBlob = NULL;
			} else {
				BlobPts *mergeBlob =
					_bps.getByID(
						_blobMembershipImg.data[rowStartPrev + x]);
				if (curBlob) {
					if ((mergeBlob) && (mergeBlob != curBlob)) {
						//curBlob = _blobMembershipImg.data[rowStartPrev + x];
					}
				} else {
					if (mergeBlob) {
						curBlob = mergeBlob;
					}
					else {
						curBlob = _bps.getClean();
					}
				}
				_blobMembershipImg.data[rowStartCur + x] = curBlob->getID();
			}
		}
		rowStartPrev = rowStartCur;
		rowStartCur += a.cols;
	}
}