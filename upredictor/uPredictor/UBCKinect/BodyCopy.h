#ifndef BODY_COPY_H
#define BODY_COPY_H

#define NOMINMAX

#include <WinSock2.h>
#include <Kinect.h>

#include "BodySegments.h"
#include "IBodyAttrs.h"

#include <opencv\cv.h>

#include <map>

//using namespace std;

class BodySegments;
class TrackIDManager;

class BodyCopy {
public:
	/*
	enum BC_MATS {
		BC_CAM_SPACE_PTS,
		BC_CAM_SPACE_LENGTHS,
		BC_DEPTH_SPACE_PTS,
		BC_ORIENTATIONS
	};
	*/

	BodyCopy(BodySegments &bs, TrackIDManager &tidm);
	~BodyCopy();

	BodySegments &getBS();
	TrackIDManager &getTIDM();

	void update(IBody *body, UINT64 kinectIndex);

	Joint *getJoints();
	JointOrientation *getOrientations();

	BOOLEAN getIsTracked();
	UINT64 getTrackingID();

	IBodyAttrs &getIBA();

	void computeCameraSpacePts();
	void computeColorSpacePts(ICoordinateMapper &cm);
	void computeDepthSpacePts(ICoordinateMapper &cm);
	
	void renderBodyOnHDBGRImage(
		cv::Mat &im
		, CvScalar &c
		, BodySegments::BSMatTypes seg);
	void renderBodyOnDepthBGRImage(
		cv::Mat &im,
		CvScalar &c
		, BodySegments::BSMatTypes seg);

	DepthSpacePoint *getDepthSP();

protected:
	void renderBodyPtsOnHDBGRImage(
		cv::Mat &im
		, CvScalar &c
		, BodySegments::BSMatTypes seg);
	void renderBodyPtsOnDepthBGRImage(
		cv::Mat &im
		, CvScalar &c
		, BodySegments::BSMatTypes seg);

	void renderBodyLinesOnHDBGRImage(
		cv::Mat &im
		, CvScalar &c
		, BodySegments::BSMatTypes seg);
	void renderBodyLinesOnDepthBGRImage(
		cv::Mat &im
		, CvScalar &c
		, BodySegments::BSMatTypes seg);

	BodySegments &_bs;
	TrackIDManager &_tidm;

	IBodyAttrs _iba;
	CameraSpacePoint _camSP[JointType_Count];
	ColorSpacePoint _colSP[JointType_Count];
	DepthSpacePoint _depSP[JointType_Count];
};

#endif