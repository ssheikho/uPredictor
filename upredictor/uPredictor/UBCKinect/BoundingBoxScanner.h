#ifndef BOUNDING_BOX_SCANNER_H
#define BOUNDING_BOX_SCANNER_H

#include "ArrayPt3DCollection.h"
#include "BoxAndConstellation.h"
#include "FrameDesc.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "SubsetPt3DCollection.h"

#include "Seb.h"

#include <opencv\cv.h>

#include <vector>

using namespace std;

class ColorBlobParams;

class BoundingBoxScanner {
public:
	BoundingBoxScanner(
		FrameDesc &fd
		, int scannerID
		, UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr> &alloc
		, ColorBlobParams &cbp);
	~BoundingBoxScanner();

	void findBB(cv::Mat &a, SimplePool<KinectFrame>::PooledPtr t);
	
	cv::Mat _checked;

protected:
	void scan(
		cv::Mat &a
		, SimplePool<KinectFrame>::PooledPtr t
		, long startX, long endX
		, long startY, long endY);

	SimplePool<BoxAndConstellation>::PooledPtr floodFillPtVect(
		cv::Mat &a
		, SimplePool<KinectFrame>::PooledPtr t
		, long startX, long startY);

	int _scannerID;
	UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr> &_alloc;
	ColorBlobParams &_cbp;
	pair<long, long> *_checkPts;
	long _fillStep;
};

#endif