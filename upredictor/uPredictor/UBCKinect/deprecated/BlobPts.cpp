#include "BlobPts.h"

BlobPts::BlobPts(int maxPts, int id) :
	_pixels(new pair<int, int>[maxPts])
	, _nPix(0), _id(id) {}

BlobPts::~BlobPts() {
	delete[] _pixels;
}

int BlobPts::getID() {
	return _id;
}

void BlobPts::addPix(int x, int y) {
	_pixels[_nPix].first = x;
	_pixels[_nPix].second = y;
	_nPix++;
}

void BlobPts::mergeIntoMe(BlobPts *bp) {
	memcpy(&_pixels[_nPix], bp->_pixels, sizeof(pair<int, int>) * bp->_nPix);
	_nPix += bp->_nPix;
	bp->_nPix = 0;
}

void BlobPts::convertRegion(cv::Mat &a, int newVal) {
	for (int i = 0; i < _nPix; i++) {
		a.data[_pixels[i].second * a.cols + _pixels[i].first] = newVal;
	}
}

void BlobPts::reset() {
	_nPix = 0;
}