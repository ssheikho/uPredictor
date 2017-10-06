#ifndef BLOB_PTS_H
#define BLOB_PTS_H

#include <opencv/cv.h>

#include <utility>

using namespace std;

class BlobPts {
public:
	BlobPts(int maxPts, int id);
	~BlobPts();

	int getID();

	void addPix(int x, int y);
	void mergeIntoMe(BlobPts *bp);
	void convertRegion(cv::Mat &a, int newVal);
	void reset();

protected:
	pair<int, int> *_pixels;
	int _nPix, _id;
};

#endif
