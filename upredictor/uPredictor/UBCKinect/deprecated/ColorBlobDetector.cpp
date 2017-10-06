#include "ColorBlobDetector.h"
#include "ColorBlobParams.h"
#include "FrameDesc.h"
#include "ProcessingParameters.h"
#include "SimpleComboBox.h"
#include "UBCUtil.h"

//#include <Blob.h>
//#include <BlobResult.h>

//#include <opencv2\photo.hpp>
#include <opencv/cv.hpp>
#include <opencv2\imgproc.hpp>

ColorBlobDetector::ColorBlobDetector(
	int detectorNumber
	, ColorBlobParams &cbp
	, FrameDesc &yuyFD
	, UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr> &alloc
	, long imageSource
	, long imageChan
	) : 
	//_detectorNumber(detectorNumber)
	//, 
	_cbp(cbp)
	, _yuyFD(yuyFD)
	, _imageSource(imageSource)
	, _imageChan(imageChan)
	, _bb(_yuyFD, detectorNumber, alloc, cbp)
	//, _bs(_yuyFD)

	, _greyOneChan(yuyFD.h, yuyFD.w, CV_8UC1)

	, _segBGR(yuyFD.h, yuyFD.w, CV_8UC3)
	, _blank(cv::Mat::zeros(yuyFD.h, yuyFD.w, CV_8UC1))
	, _seg(_blank)
	, _clicked(false)
	, _dragged(false)
	, _clickLoc(pair<int,int>(0,0))
{
	for (int i = 0; i < CBD_BGR_CHANNEL_COUNT; i++) {
		_bgrSplit.push_back(cv::Mat(yuyFD.h, yuyFD.w, CV_8UC1));
		_mostly[i] = new MostlyOneColor(yuyFD);
	}
	
	_segmentMats[CBD_BGR_B] = &_bgrSplit[CBD_B];
	_segmentMats[CBD_BGR_G] = &_bgrSplit[CBD_G];
	_segmentMats[CBD_BGR_R] = &_bgrSplit[CBD_R];

	_segmentMats[CBD_BGR_MB] = &_mostly[CBD_B]->_detected;
	_segmentMats[CBD_BGR_MG] = &_mostly[CBD_G]->_detected;
	_segmentMats[CBD_BGR_MR] = &_mostly[CBD_R]->_detected;

	_segmentMats[CBD_BGR_MBTG] = &_mostly[CBD_B]->_aMinusB;
	_segmentMats[CBD_BGR_MBTR] = &_mostly[CBD_B]->_aMinusC;
	_segmentMats[CBD_BGR_MGTB] = &_mostly[CBD_G]->_aMinusB;
	_segmentMats[CBD_BGR_MGTR] = &_mostly[CBD_G]->_aMinusC;
	_segmentMats[CBD_BGR_MRTB] = &_mostly[CBD_R]->_aMinusB;
	_segmentMats[CBD_BGR_MRTG] = &_mostly[CBD_R]->_aMinusC;

	//_segmentMats[CBD_BGR_GRADX] = &_gradXGray;
	//_segmentMats[CBD_BGR_GRADY] = &_gradYGray;
}

ColorBlobDetector::~ColorBlobDetector() {
	for (int i = 0; i < CBD_BGR_CHANNEL_COUNT; i++) {
		delete _mostly[i];
	}
}

ColorBlobParams &ColorBlobDetector::getCBP() {
	return _cbp;
}

BoundingBoxScanner &ColorBlobDetector::getBB() {
	return _bb;
}

void ColorBlobDetector::processType(SimplePool<KinectFrame>::PooledPtr t) {
	long majorityChan = _cbp._majorityColorChannel._t;
	//double gradThresh = _cbp._gradientThresh._t;

	cv::Mat &bgr = t->getImageChannel(_imageSource, _imageChan);
	//cv::Mat &gradX =
	//	t->getImageChannel(KinectFrame::KF_SOURCE_DEPTH_32FC1
	//		, KinectFrame::KF_DEPTH32FC1_GRADX);
	//cv::Mat &gradY =
	//	t->getImageChannel(KinectFrame::KF_SOURCE_DEPTH_32FC1
	//		, KinectFrame::KF_DEPTH32FC1_GRADY);

	cv:cvtColor(bgr, _greyOneChan, CV_BGR2GRAY, 1);

	cv::split(bgr, _bgrSplit);

	//cv::threshold(gradX, _gradXT, gradThresh, 255, CV_THRESH_BINARY);
	//cv::threshold(gradY, _gradYT, gradThresh, 255, CV_THRESH_BINARY);

	switch (majorityChan) {
	case CBD_B:
		_mostly[CBD_B]->process(
			_bgrSplit[CBD_B]
			, _bgrSplit[CBD_G], _cbp._bMinusGThresh._t
			, _bgrSplit[CBD_R], _cbp._bMinusRThresh._t);

		//_bs.findBlobs(_mostly[CBD_B]->_detected);
		_bb.findBB(_mostly[CBD_B]->_detected, t);
		_seg = _mostly[CBD_B]->_detected;
		break;
	case CBD_G:
		_mostly[CBD_G]->process(
			_bgrSplit[CBD_G]
			, _bgrSplit[CBD_B], _cbp._gMinusBThresh._t
			, _bgrSplit[CBD_R], _cbp._gMinusRThresh._t);

		//_bs.findBlobs(_mostly[CBD_G]->_detected);
		_bb.findBB(_mostly[CBD_G]->_detected, t);
		_seg = _mostly[CBD_G]->_detected;
		break;
	case CBD_R:
		_mostly[CBD_R]->process(
			_bgrSplit[CBD_R]
			, _bgrSplit[CBD_B], _cbp._rMinusBThresh._t
			, _bgrSplit[CBD_G], _cbp._rMinusGThresh._t);

		//_bs.findBlobs(_mostly[CBD_R]->_detected);
		_bb.findBB(_mostly[CBD_R]->_detected, t);
		_seg = _mostly[CBD_R]->_detected;
		break;
	}

	reportColors(t, majorityChan);
		
	TypeBroadcaster<ImageChannelProvider *>::fireUpdate(this);
}

void ColorBlobDetector::reportColors(
	SimplePool<KinectFrame>::PooledPtr t
	, long majorityChan) {
	if (_clicked) {
		cv::Point p(_clickLoc.first, _clickLoc.second);
		cv::Scalar s(
			_bgrSplit[0].at<uint8_t>(p)
			, _bgrSplit[1].at<uint8_t>(p)
			, _bgrSplit[2].at<uint8_t>(p)
			);
		_clicked = false;
		TypeBroadcaster<cv::Scalar>::fireUpdate(s);
	}

	if (_dragged) {
		cv::Point p(_draggedLoc._min.first, _draggedLoc._min.second);

		uint8_t minB = _bgrSplit[0].at<uint8_t>(p);
		uint8_t minG = _bgrSplit[1].at<uint8_t>(p);
		uint8_t minR = _bgrSplit[2].at<uint8_t>(p);
		uint8_t maxB = minB;
		uint8_t maxG = minG;
		uint8_t maxR = minR;

		uint8_t minMarg = _segmentMats[majorityChan]->at<uint8_t>(p);
		uint8_t maxMarg = minMarg;

		for (
			int curX = _draggedLoc._min.first
			; curX <= _draggedLoc._max.first
			; curX++) {
			for (
				int curY = _draggedLoc._min.second
				; curY <= _draggedLoc._max.second
				; curY++) {
				p = cv::Point(curX, curY);
				uint8_t curB = _bgrSplit[0].at<uint8_t>(p);
				uint8_t curG = _bgrSplit[1].at<uint8_t>(p);
				uint8_t curR = _bgrSplit[2].at<uint8_t>(p);

				uint8_t curMarg = _segmentMats[majorityChan]->at<uint8_t>(p);

				if (curB > maxB) maxB = curB;
				if (curB < minB) minB = curB;
				if (curG > maxG) maxG = curG;
				if (curG < minG) minG = curG;
				if (curR > maxR) maxR = curR;
				if (curR < minR) minR = curR;

				if (curMarg > maxMarg) maxMarg = curMarg;
				if (curMarg < minMarg) minMarg = curMarg;
			}
		}

		cv::Scalar minS(minB, minG, minR);
		cv::Scalar maxS(maxB, maxG, maxR);

		TypeBroadcaster<pair<cv::Scalar, cv::Scalar>>::
			fireUpdate(pair<cv::Scalar, cv::Scalar>(minS, maxS));

		TypeBroadcaster<pair<uint8_t, uint8_t>>::
			fireUpdate(pair<uint8_t, uint8_t>(minMarg, maxMarg));

		_dragged = false;
	}

	drawCrosshair(t->_bgr, _clickLoc.first, _clickLoc.second, 5,
		5, CvScalar(255, 255, 255));

	drawCrosshair(t->_bgr, _draggedLoc._a.first, _draggedLoc._a.second, 5,
		5, CvScalar(255, 0, 255));
	drawCrosshair(t->_bgr, _draggedLoc._b.first, _draggedLoc._b.second, 5,
		5, CvScalar(255, 0, 255));

	cv::rectangle(t->_bgr
		, cv::Point(_draggedLoc._min.first, _draggedLoc._min.second)
		, cv::Point(_draggedLoc._max.first, _draggedLoc._max.second)
		, CvScalar(255, 0, 255));
}

void ColorBlobDetector::processType(pair<int, int> t) {
	_clicked = true;
	_clickLoc = pair<int,int>(_yuyFD.w - t.first, t.second);
}

void ColorBlobDetector::processType(DragRect t) {
	_dragged = true;
	_draggedLoc = t;
	_draggedLoc.invertXBy(_yuyFD.w);
}

void ColorBlobDetector::populateVideoChannelCB(SimpleComboBox *scb) {
	scb->addSelection(L"CBD_BGR_R", CBD_BGR_R);
	scb->addSelection(L"CBD_BGR_G", CBD_BGR_G);
	scb->addSelection(L"CBD_BGR_B", CBD_BGR_B);

	scb->addSelection(L"CBD_BGR_MR", CBD_BGR_MR);
	scb->addSelection(L"CBD_BGR_MG", CBD_BGR_MG);
	scb->addSelection(L"CBD_BGR_MB", CBD_BGR_MB);

	scb->addSelection(L"CBD_BGR_MRTB", CBD_BGR_MRTB);
	scb->addSelection(L"CBD_BGR_MRTG", CBD_BGR_MRTG);
	scb->addSelection(L"CBD_BGR_MGTB", CBD_BGR_MGTB);
	scb->addSelection(L"CBD_BGR_MGTR", CBD_BGR_MGTR);
	scb->addSelection(L"CBD_BGR_MBTR", CBD_BGR_MBTR);
	scb->addSelection(L"CBD_BGR_MBTG", CBD_BGR_MBTG);
}

void ColorBlobDetector::populateBGRChannelCB(SimpleComboBox *scb) {
	scb->addSelection(L"CBD_B", CBD_B);
	scb->addSelection(L"CBD_G", CBD_G);
	scb->addSelection(L"CBD_R", CBD_R);
}

cv::Mat ColorBlobDetector::getImageChannel(size_t source, size_t index) {
	vector<cv::Mat> m;
	m.push_back(_greyOneChan);
	//m.push_back(_bs.getMembershipImg());
	m.push_back(_bb._checked);
	m.push_back(*_segmentMats[index]);

	cv::merge(m, _segBGR);

	return _segBGR;
}

cv::Mat ColorBlobDetector::getSeg() {
	return _seg;
}

ColorBlobDetector::MostlyOneColor::MostlyOneColor(FrameDesc &yuyFD) :
	_aMinusB(yuyFD.h, yuyFD.w, CV_8UC1)
	, _aMinusC(yuyFD.h, yuyFD.w, CV_8UC1)
	, _aThreshB(yuyFD.h, yuyFD.w, CV_8UC1)
	, _aThreshC(yuyFD.h, yuyFD.w, CV_8UC1)
	, _detected(yuyFD.h, yuyFD.w, CV_8UC1)
{}

ColorBlobDetector::MostlyOneColor::~MostlyOneColor() {}

void ColorBlobDetector::MostlyOneColor::process(
	cv::Mat &a
	, cv::Mat &b, long bMargin
	, cv::Mat &c, long cMargin) {
	cv::subtract(a, b, _aMinusB);
	cv::subtract(a, c, _aMinusC);

	cv::threshold(_aMinusB, _aThreshB, bMargin, 255, CV_THRESH_BINARY);
	cv::threshold(_aMinusC, _aThreshC, cMargin, 255, CV_THRESH_BINARY);

	cv::bitwise_and(_aThreshB, _aThreshC, _detected);
}