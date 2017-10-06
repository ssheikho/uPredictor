#include "HandFinder.h"
#include "BodyCopyCollection.h"
#include "KinectFrame.h"
#include "ProcessingParameters.h"
#include "UBCUtil.h"

#include <opencv2\imgproc.hpp>

#include <cmath>

HandFinder::HandFinder(
	KinectFrame *kf
	, ProcessingParameters &pp
	, BodyCopyCollection &bcc
	, cv::Mat &depthD
	, cv::Mat &depthThresh
	, cv::Mat &depthL
	, cv::Mat &depthLGrey
	, cv::Mat &blankDepth8UC1
	, cv::Mat &depthLBGR
	) :
	_kf(kf)
	, _pp(pp)
	, _bcc(bcc)
	, _depthD(depthD)
	, _depthThresh(depthThresh)
	, _depthL(depthL)
	, _depthLGrey(depthLGrey)
	, _blankDepth8UC1(blankDepth8UC1)
	, _depthLBGR(depthLBGR)
	{}

HandFinder::~HandFinder() {}

void HandFinder::findHand(
	size_t bodyIndex
	) {

	//cv::Canny(_depthThresh, _depthL, 50, 150);
	cv::Sobel(_depthThresh, _depthL, CV_32F, 0, 1);

	_depthL.convertTo(_depthLGrey, CV_8UC1
		, -255.0f / _pp.getGradientParam1()._t, 255.0f);

	vector<cv::Mat> m;
	m.push_back(_depthLGrey);
	m.push_back(_depthLGrey);
	m.push_back(_blankDepth8UC1);

	cv::merge(m, _depthLBGR);
	_kf->renderBodyOnDepthBGRImage(_depthLBGR);

	BodyCopy *bc = _bcc.getBC(bodyIndex);
	DepthSpacePoint a = bc->getDepthSP()[JointType_HandRight];
	DepthSpacePoint b = bc->getDepthSP()[JointType_WristRight];
	CvPoint dsp = CvPoint((a.X + b.X) / 2.0, (a.Y + b.Y) / 2.0);
	findMaxMinSweepSpan(pair<float, float>(dsp.x, dsp.y), 5);
}

pair<float, float> HandFinder::findEndInDir(
	pair<float, float> midPt
	, float handD
	, float dX
	, float dY
	, float angle
	) {
	float dThetaX = cos(angle);
	float dThetaY = sin(angle);

	pair<float, float> end =
		pair<float, float>(
			midPt.first + dThetaX
			, midPt.second + dThetaY
			);

	float distY = end.second - midPt.second;
	float distX = end.first - midPt.first;
	float minD = handD - abs(distY * dY + distX * dX);
	float maxD = handD + abs(distY * dY + distX * dX);
	float endD = _depthD.at<float>(end.second, end.first);

	while (
		((minD < endD) && (endD < maxD)) &&
		((0 < (end.first + dThetaX)) && ((end.first + dThetaX) < _depthD.cols)) &&
		((0 < (end.second + dThetaY)) && ((end.second + dThetaY) < _depthD.rows))
		) {
		end.first += dThetaX;
		end.second += dThetaY;
		distY = end.second - midPt.second;
		distX = end.first - midPt.first;
		minD = handD - abs(distY * dY + distX * dX);
		maxD = handD + abs(distY * dY + distX * dX);
		endD = _depthD.at<float>(end.second, end.first);
	}

	return end;
}

HandFinder::ScanPts HandFinder::findSpan(
	pair<float, float> midPt
	, float handD
	, float dX
	, float dY
	, float angle) {
	ScanPts retVal;

	retVal._bot = findEndInDir(
		midPt
		, handD
		, dX, dY
		, angle
		);

	retVal._top = findEndInDir(
midPt
, handD
, dX, dY
, angle + 3.14
);

//retVal._mid.first = (retVal._bot.first + retVal._top.first) / 2;
//retVal._mid.second = (retVal._bot.second + retVal._top.second) / 2;

return retVal;
}

vector<HandFinder::ScanPts> HandFinder::sweepSpan(
	pair<float, float> midPt
	, float handD
	, float dX
	, float dY
	, int divs) {
	vector<HandFinder::ScanPts> retVal;

	float incr = 3.14f / float(divs);
	float theta = 0.0f;
	for (int i = 0; i < divs; i++) {
		retVal.push_back(findSpan(midPt, handD, dX, dY, theta));
		theta += incr;
	}

	return retVal;
}

void HandFinder::drawCrosshairs(ScanPts pts, cv::Mat &bgr) {
	drawCrosshair(
		bgr
		, pts._bot.first
		, pts._bot.second
		, 5, 2, CvScalar(0, 0, 255));
	/*
	drawCrosshair(
		bgr
		, pts._mid.first
		, pts._mid.second
		, 5, 2, CvScalar(0, 0, 255));
	*/
	drawCrosshair(
		bgr
		, pts._top.first
		, pts._top.second
		, 5, 2, CvScalar(0, 0, 255));

	CvPoint ptA, ptB;
	ptA.x = pts._bot.first;
	ptA.y = pts._bot.second;
	ptB.x = pts._top.first;
	ptB.y = pts._top.second;

	cv::line(bgr, ptA, ptB, CvScalar(0, 255, 0), 4, 8, 0);
}

float HandFinder::maxMinSweepSpan(
	pair<float, float> midPt
	, float handD
	, float dX
	, float dY
	, int divs) {
	vector<ScanPts> lines = sweepSpan(
		midPt
		, handD
		, dX
		, dY
		, divs);

	//int lineNo = 0;
	float val = scanPtsDist(lines[0]);
	for (int i = 1; i < lines.size(); i++) {
		float a = scanPtsDist(lines[i]);
		if (a < val) {
			//lineNo = i;
			val = a;
		}
	}

	drawCrosshairs(lines, _depthLBGR);

	return val;
}

float HandFinder::maxMinSweepSpan(
	pair<float, float> midPt
	, int divs
	) {
	double deltaTolerance = _pp.getGradientParam1()._t;

	float handD = _depthD.at<float>(midPt.second, midPt.first);

	float depthUp = _depthD.at<float>(midPt.second - 1, midPt.first);
	float depthDown = _depthD.at<float>(midPt.second + 1, midPt.first);
	float depthLeft = _depthD.at<float>(midPt.second, midPt.first - 1);
	float depthRight = _depthD.at<float>(midPt.second, midPt.first + 1);

	float dY = ((depthUp - depthDown) / 2.0f) * deltaTolerance;
	float dX = ((depthLeft - depthRight) / 2.0f) * deltaTolerance;

	_pp.getHandDepth().processType(handD);
	_pp.getHandDY().processType(dY);
	_pp.getHandDX().processType(dX);

	return maxMinSweepSpan(midPt, handD, dX, dY, 4);
}

void HandFinder::findMaxMinSweepSpan(pair<float, float> midPt, int divs) {
	double deltaTolerance = _pp.getGradientParam2()._t;

	float dY = 0.0f;
	float dX = 0.0f;
	float dist = 0.0f;
	do {
		float upSpan = maxMinSweepSpan(
			pair<float, float>(midPt.first, midPt.second - 1), divs);
		float downSpan = maxMinSweepSpan(
			pair<float, float>(midPt.first, midPt.second + 1), divs);
		float leftSpan = maxMinSweepSpan(
			pair<float, float>(midPt.first, midPt.second - 1), divs);
		float rightSpan = maxMinSweepSpan(
			pair<float, float>(midPt.first, midPt.second + 1), divs);

		dY = (upSpan - downSpan) * deltaTolerance;
		dX = (leftSpan - rightSpan) * deltaTolerance;

		midPt.first += dX;
		midPt.second += dY;
		dist = sqrt((dY * dY) + (dX * dX));
	} while (dist > 1.0f);
}

float HandFinder::scanPtsDist(ScanPts pts) {
	float a = pts._bot.first - pts._top.first;
	float b = pts._bot.second - pts._top.second;
	return sqrt(a * a + b * b);
}

void HandFinder::drawCrosshairs(vector<ScanPts> pts, cv::Mat &bgr) {
	for (int i = 0; i < pts.size(); i++) drawCrosshairs(pts[i], bgr);
}