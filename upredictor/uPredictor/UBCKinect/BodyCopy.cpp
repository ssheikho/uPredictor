#include "BodyCopy.h"
#include "BodySegments.h"
#include "TrackIDManager.h"
#include "UBCUtil.h"

#include <opencv2\imgproc.hpp>

BodyCopy::BodyCopy(BodySegments &bs, TrackIDManager &tidm) :
	_bs(bs)
	, _tidm(tidm) {}

BodyCopy::~BodyCopy() {}

BodySegments &BodyCopy::getBS() {
	return _bs;
}

TrackIDManager &BodyCopy::getTIDM() {
	return _tidm;
}

void BodyCopy::update(IBody *body, UINT64 kinectIndex) {
	if (body) {
		body->get_IsTracked(&_iba._isTracked);
		if (_iba._isTracked) {
			UINT64 trackingID;
			body->GetJoints(JointType_Count, _iba._joints);
			body->GetJointOrientations(JointType_Count, _iba._orientations);
			body->get_TrackingId(&trackingID);
			_iba._trackingID = _tidm.getTrackID(kinectIndex, trackingID);
		}
	}
	else {
		_iba._isTracked = FALSE;
	}
}

Joint *BodyCopy::getJoints() {
	return _iba._joints;
}

JointOrientation *BodyCopy::getOrientations() {
	return _iba._orientations;
}

BOOLEAN BodyCopy::getIsTracked() {
	return _iba._isTracked;
}

UINT64 BodyCopy::getTrackingID() {
	return _iba._trackingID;
}

IBodyAttrs &BodyCopy::getIBA() {
	return _iba;
}

void BodyCopy::computeCameraSpacePts() {
	kinectJointPositionDump(_iba._joints, _camSP, JointType_Count);
}

void BodyCopy::computeColorSpacePts(ICoordinateMapper &cm) {
	cm.MapCameraPointsToColorSpace(
		JointType_Count, _camSP,
		JointType_Count, _colSP);
}

void BodyCopy::computeDepthSpacePts(ICoordinateMapper &cm) {
	cm.MapCameraPointsToDepthSpace(
		JointType_Count, _camSP,
		JointType_Count, _depSP);
}

/*
CvScalar yellow = cvScalar(255, 255, 255);
CvScalar green = cvScalar(0, 255, 0);
CvScalar red = cvScalar(255, 0, 0);
*/
	
void BodyCopy::renderBodyOnHDBGRImage(
	cv::Mat &im
	, CvScalar &c
	, BodySegments::BSMatTypes seg) {
	if (_iba._isTracked == TRUE) {
		renderBodyPtsOnHDBGRImage(im, c, seg);
		renderBodyLinesOnHDBGRImage(im, c, seg);
	}
}

void BodyCopy::renderBodyOnDepthBGRImage(
	cv::Mat &im
	, CvScalar &c
	, BodySegments::BSMatTypes seg) {
	if (_iba._isTracked == TRUE) {
		renderBodyPtsOnDepthBGRImage(im, c, seg);
		renderBodyLinesOnDepthBGRImage(im, c, seg);
	}
}

void BodyCopy::renderBodyPtsOnHDBGRImage(
	cv::Mat &im
	, CvScalar &c
	, BodySegments::BSMatTypes seg) {
	Eigen::MatrixXi &ptMat = _bs.getPts(seg);
	for (size_t i = 0; i < ptMat.cols(); i++)
		if(_iba._joints[i].TrackingState == TrackingState_Tracked)
			drawCrosshair(
				im
				, _colSP[ptMat(0,i)].X
				, _colSP[ptMat(0, i)].Y
				, 5, 2, c);
}

void BodyCopy::renderBodyPtsOnDepthBGRImage(
	cv::Mat &im
	, CvScalar &c
	, BodySegments::BSMatTypes seg) {
	Eigen::MatrixXi &ptMat = _bs.getPts(seg);
	for (size_t i = 0; i < ptMat.cols(); i++)
		if (_iba._joints[i].TrackingState == TrackingState_Tracked)
			drawCrosshair(im, _depSP[ptMat(0, i)].X, _depSP[ptMat(0, i)].Y, 5, 2, c);
}

void BodyCopy::renderBodyLinesOnHDBGRImage(
	cv::Mat &im
	, CvScalar &c
	, BodySegments::BSMatTypes seg) {
	Eigen::MatrixXi &linkMat = _bs.getLinks(seg);
	for (size_t i = 0; i < linkMat.cols(); i++) {
		size_t from = (size_t)linkMat(0, i);
		size_t to = (size_t)linkMat(1, i);
		if (
			(_iba._joints[from].TrackingState == TrackingState_Tracked) &&
			(_iba._joints[to].TrackingState == TrackingState_Tracked)
			) {
			cv::line(im
				, cv::Point(_colSP[from].X, _colSP[from].Y)
				, cv::Point(_colSP[to].X, _colSP[to].Y)
				, c
				);
		}
	}
}

void BodyCopy::renderBodyLinesOnDepthBGRImage(
	cv::Mat &im
	, CvScalar &c
	, BodySegments::BSMatTypes seg) {
	Eigen::MatrixXi &linkMat = _bs.getLinks(seg);
	for (size_t i = 0; i < linkMat.cols(); i++) {
		size_t from = (size_t)linkMat(0, i);
		size_t to = (size_t)linkMat(1, i);
		if (
			(_iba._joints[from].TrackingState == TrackingState_Tracked) &&
			(_iba._joints[to].TrackingState == TrackingState_Tracked)
			) {
			cv::line(im
				, cv::Point(_depSP[from].X, _depSP[from].Y)
				, cv::Point(_depSP[to].X, _depSP[to].Y)
				, c
				);
		}
	}
}

DepthSpacePoint *BodyCopy::getDepthSP() {
	return _depSP;
}