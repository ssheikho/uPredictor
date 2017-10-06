#ifndef HAND_FINDER_H
#define HAND_FINDER_H

#include <WinSock2.h>
#include <Kinect.h>

#include <opencv/cv.h>

#include <utility>

using namespace std;

class BodyCopyCollection;
struct KinectFrame;
class ProcessingParameters;

//stackoverflow.com/questions/4279478/
//largest-circle-inside-a-non-convex-polygon

class HandFinder {
public:
	HandFinder(
		KinectFrame *kf
		, ProcessingParameters &pp
		, BodyCopyCollection &bcc
		, cv::Mat &depthD
		, cv::Mat &depthThresh
		, cv::Mat &depthL
		, cv::Mat &depthLGrey
		, cv::Mat &blankDepth8UC1
		, cv::Mat &depthLBGR
		);
	~HandFinder();

	void findHand(
		size_t bodyIndex
		);

protected:
	struct ScanPts {
		pair<float, float> _bot, _top;
	};

	pair<float, float> findEndInDir(
		pair<float, float> midPt
		, float handD
		, float dX
		, float dY
		, float angle
		);

	ScanPts findSpan(
		pair<float, float> midPt
		, float handD
		, float dX
		, float dY
		, float angle);

	vector<ScanPts> sweepSpan(
		pair<float, float> midPt
		, float handD
		, float dX
		, float dY
		, int divs);

	float maxMinSweepSpan(
		pair<float, float> midPt
		, float handD
		, float dX
		, float dY
		, int divs);

	float maxMinSweepSpan(pair<float, float> midPt, int divs);

	void findMaxMinSweepSpan(pair<float, float> midPt, int divs);

	float scanPtsDist(ScanPts pts);

	void drawCrosshairs(ScanPts pts, cv::Mat &bgr);
	void drawCrosshairs(vector<ScanPts> pts, cv::Mat &bgr);

	KinectFrame *_kf;
	ProcessingParameters &_pp;
	BodyCopyCollection &_bcc;
	cv::Mat
		&_depthD
		, &_depthThresh
		, &_depthL
		, &_depthLGrey
		, &_blankDepth8UC1
		, &_depthLBGR;
};

#endif