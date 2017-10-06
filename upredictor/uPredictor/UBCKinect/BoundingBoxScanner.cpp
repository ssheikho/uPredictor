#include "BoundingBoxScanner.h"
#include "ColorBlobParams.h"
#include "Point3DRGB.h"
#include <queue>

//Ritters algorithm, modified for the largest bounding and osculating circles.
BoundingBoxScanner::BoundingBoxScanner(
	FrameDesc &fd
	, int scannerID
	, UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr> &alloc
	, ColorBlobParams &cbp) :
	_checked(fd.h, fd.w, CV_8UC1)
	, _scannerID(scannerID)
	, _alloc(alloc)
	, _cbp(cbp)
	, _checkPts(new pair<long,long>[fd.h * fd.w * 4])
	, _fillStep(1) {}

BoundingBoxScanner::~BoundingBoxScanner() {
	delete[] _checkPts;
}

void BoundingBoxScanner::findBB(
	cv::Mat &a
	, SimplePool<KinectFrame>::PooledPtr t) {
	memset(_checked.data, 0, sizeof(uint8_t) * _checked.rows * _checked.cols);
	scan(a, t, 0, a.cols, 0, a.rows);
}

void BoundingBoxScanner::scan(
	cv::Mat &a
	, SimplePool<KinectFrame>::PooledPtr t
	, long startX, long endX
	, long startY, long endY) {
	t->_boxes[_scannerID].clear();
	int nBoxes = 0;
	for (int y = startY; y < endY; y++) {
		int yOffset = y * a.cols;
		for (int x = startX; x < endX; x++) {
			if(nBoxes < _cbp.getMaxBoxes())
			if ((a.data[yOffset + x]) && (!_checked.data[yOffset + x])) {
				SimplePool<BoxAndConstellation>::PooledPtr bb =
					floodFillPtVect(a, t, x, y);
				if(bb->getPts()->getNPts() >= _cbp._minBlobPts._t)
					t->_boxes[_scannerID].push_back(bb);
			}
		}
	}
}

SimplePool<BoxAndConstellation>::PooledPtr BoundingBoxScanner::floodFillPtVect(
	cv::Mat &a
	, SimplePool<KinectFrame>::PooledPtr t
	, long startX, long startY) {
	ArrayPt3DCollection &reg = t->_pts;
	CameraSpacePoint *pts3D = reg.getCameraPts();

	SimplePool<BoxAndConstellation>::PooledPtr bb =
		_alloc.getInstance();
	SimplePool<SubsetPt3DCollection>::PooledPtr pts = bb->getPts();
	pts->clear();
	pts->setSuperset(&reg);

	int endY = a.cols * a.rows;

	uint8_t *data = a.data;
	uint8_t *checked = _checked.data;
	_checkPts[0].first = startX;
	_checkPts[0].second = startY;
	int nPts = 1;

	double minX2D = startX;	double maxX2D = startX;
	double minY2D = startY;	double maxY2D = startY;

	long bmpPos = a.cols * startY + startX;

	//double curX3D = pts3D[bmpPos]._x3D;
	//double curY3D = pts3D[bmpPos]._y3D;
	//double curZ3D = pts3D[bmpPos]._z3D;
	double curX3D = pts3D[bmpPos].X;
	double curY3D = pts3D[bmpPos].Y;
	double curZ3D = pts3D[bmpPos].Z;
	double minX3D = curX3D;	double maxX3D = curX3D;
	double minY3D = curY3D;	double maxY3D = curY3D;
	double minZ3D = curZ3D;	double maxZ3D = curZ3D;

	while (nPts > 0) {
		nPts--;
		double curX2D = _checkPts[nPts].first;
		double curY2D = _checkPts[nPts].second;
		bmpPos = (long)(a.cols * (long)curY2D + (long)curX2D);

		if ((checked[bmpPos] == 0) && (data[bmpPos] > 0)) {
			//curX3D = pts3D[bmpPos]._x3D;
			//curY3D = pts3D[bmpPos]._y3D;
			//curZ3D = pts3D[bmpPos]._z3D;
			curX3D = pts3D[bmpPos].X;
			curY3D = pts3D[bmpPos].Y;
			curZ3D = pts3D[bmpPos].Z;

			if (curX2D < minX2D) minX2D = curX2D;
			if (curX2D > maxX2D) maxX2D = curX2D;
			if (curY2D < minY2D) minY2D = curY2D;
			if (curY2D > maxY2D) maxY2D = curY2D;

			if (curX3D < minX3D) minX3D = curX3D;
			if (curX3D > maxX3D) maxX3D = curX3D;
			if (curY3D < minY3D) minY3D = curY3D;
			if (curY3D > maxY3D) maxY3D = curY3D;
			if (curZ3D < minZ3D) minZ3D = curZ3D;
			if (curZ3D > maxZ3D) maxZ3D = curZ3D;

			pts->addIndex(bmpPos);

			int backX = (long)curX2D - 1;
			int fwdX = (long)curX2D + 1;
			int backY = (long)curY2D - 1;
			int fwdY = (long)curY2D + 1;

			if (backX >= 0) {
				_checkPts[nPts].first = backX;
				_checkPts[nPts].second = curY2D;
				nPts++;
			}

			if (fwdX < a.cols) {
				_checkPts[nPts].first = fwdX;
				_checkPts[nPts].second = curY2D;
				nPts++;
			}

			if (backY >= 0) {
				_checkPts[nPts].first = curX2D;
				_checkPts[nPts].second = backY;
				nPts++;
			}

			if (fwdY < endY) {
				_checkPts[nPts].first = curX2D;
				_checkPts[nPts].second = fwdY;
				nPts++;
			}

		}
		checked[bmpPos] = 255;
		//pts->copyIntoCollection(t->_reg.getPt(bmpPos));
	}

	bb->getBB().updateBounds(
		minX2D, maxX2D,
		minY2D, maxY2D,
		minX3D, maxX3D,
		minY3D, maxY3D,
		minZ3D, maxZ3D);

	pts->compile();
	return bb;
}