#include "BodySegments.h"

BodySegments::BodySegments() :
	_allLinks(2, (int)BS_SEGMENT_COUNT)
	, _allPts(1, (int)JointType_Count)
	, _rightArmLinks(2, 3)
	, _rightArmPts(1, 4)
{
	_allLinks(0, BS_SPINEBASE_SPINEMID) = JointType_SpineBase;
	_allLinks(1, BS_SPINEBASE_SPINEMID) = JointType_SpineMid;

	_allLinks(0, BS_SPINEMID_SPINESHOULDER) = JointType_SpineMid;
	_allLinks(1, BS_SPINEMID_SPINESHOULDER) = JointType_SpineShoulder;

	_allLinks(0, BS_SPINESHOULDER_NECK) = JointType_SpineShoulder;
	_allLinks(1, BS_SPINESHOULDER_NECK) = JointType_Neck;

	_allLinks(0, BS_NECK_HEAD) = JointType_Neck;
	_allLinks(1, BS_NECK_HEAD) = JointType_Head;

	_allLinks(0, BS_SPINESHOULDER_SHOULDERL) = JointType_SpineShoulder;
	_allLinks(1, BS_SPINESHOULDER_SHOULDERL) = JointType_ShoulderLeft;

	_allLinks(0, BS_SPINESHOULDER_SHOULDERR) = JointType_SpineShoulder;
	_allLinks(1, BS_SPINESHOULDER_SHOULDERR) = JointType_ShoulderRight;

	_allLinks(0, BS_SHOULDERL_ELBOWL) = JointType_ShoulderLeft;
	_allLinks(1, BS_SHOULDERL_ELBOWL) = JointType_ElbowLeft;

	_allLinks(0, BS_SHOULDERR_ELBOWR) = JointType_ShoulderRight;
	_allLinks(1, BS_SHOULDERR_ELBOWR) = JointType_ElbowRight;

	_allLinks(0, BS_ELBOWL_WRISTL) = JointType_ElbowLeft;
	_allLinks(1, BS_ELBOWL_WRISTL) = JointType_WristLeft;

	_allLinks(0, BS_ELBOWR_WRISTR) = JointType_ElbowRight;
	_allLinks(1, BS_ELBOWR_WRISTR) = JointType_WristRight;

	_allLinks(0, BS_WRISTL_HANDL) = JointType_WristLeft;
	_allLinks(1, BS_WRISTL_HANDL) = JointType_HandLeft;

	_allLinks(0, BS_WRISTR_HANDR) = JointType_WristRight;
	_allLinks(1, BS_WRISTR_HANDR) = JointType_HandRight;

	_allLinks(0, BS_HANDL_HANDTIPL) = JointType_HandLeft;
	_allLinks(1, BS_HANDL_HANDTIPL) = JointType_HandTipLeft;

	_allLinks(0, BS_HANDR_HANDTIPR) = JointType_HandRight;
	_allLinks(1, BS_HANDR_HANDTIPR) = JointType_HandTipRight;

	_allLinks(0, BS_HANDL_THUMBL) = JointType_HandLeft;
	_allLinks(1, BS_HANDL_THUMBL) = JointType_ThumbLeft;

	_allLinks(0, BS_HANDR_THUMBR) = JointType_HandRight;
	_allLinks(1, BS_HANDR_THUMBR) = JointType_ThumbRight;

	_allLinks(0, BS_SPINEBASE_HIPL) = JointType_SpineBase;
	_allLinks(1, BS_SPINEBASE_HIPL) = JointType_HipLeft;

	_allLinks(0, BS_SPINEBASE_HIPR) = JointType_SpineBase;
	_allLinks(1, BS_SPINEBASE_HIPR) = JointType_HipRight;

	_allLinks(0, BS_HIPL_KNEEL) = JointType_HipLeft;
	_allLinks(1, BS_HIPL_KNEEL) = JointType_KneeLeft;

	_allLinks(0, BS_HIPR_KNEER) = JointType_HipRight;
	_allLinks(1, BS_HIPR_KNEER) = JointType_KneeRight;

	_allLinks(0, BS_KNEEL_ANKLEL) = JointType_KneeLeft;
	_allLinks(1, BS_KNEEL_ANKLEL) = JointType_AnkleLeft;

	_allLinks(0, BS_KNEER_ANKLER) = JointType_KneeRight;
	_allLinks(1, BS_KNEER_ANKLER) = JointType_AnkleRight;

	_allLinks(0, BS_ANKLEL_FOOTL) = JointType_AnkleLeft;
	_allLinks(1, BS_ANKLEL_FOOTL) = JointType_FootLeft;

	_allLinks(0, BS_ANKLER_FOOTR) = JointType_AnkleRight;
	_allLinks(1, BS_ANKLER_FOOTR) = JointType_FootRight;

	for (int i = 0; i < JointType_Count; i++)
		_allPts(0, i) = i;

	_rightArmLinks(0, 0) = JointType_ShoulderRight;
	_rightArmLinks(1, 0) = JointType_ElbowRight;
	_rightArmLinks(0, 1) = JointType_ElbowRight;
	_rightArmLinks(1, 1) = JointType_WristRight;
	_rightArmLinks(0, 2) = JointType_WristRight;
	_rightArmLinks(1, 2) = JointType_HandRight;

	_rightArmPts(0, 0) = JointType_ShoulderRight;
	_rightArmPts(0, 1) = JointType_ElbowRight;
	_rightArmPts(0, 2) = JointType_WristRight;
	_rightArmPts(0, 3) = JointType_HandRight;

	_linkMats[BS_ALL] = &_allLinks;
	_ptMats[BS_ALL] = &_allPts;

	_linkMats[BS_RIGHT_ARM] = &_rightArmLinks;
	_ptMats[BS_RIGHT_ARM] = &_rightArmPts;
}

BodySegments::~BodySegments() {}

MatrixXi &BodySegments::getLinks(BodySegments::BSMatTypes seg) {
	return *_linkMats[seg];
}

MatrixXi &BodySegments::getPts(BodySegments::BSMatTypes seg) {
	return *_ptMats[seg];
}

MatrixXi &BodySegments::getAllLinks() {
	return _allLinks;
}

MatrixXi &BodySegments::getAllPts() {
	return _allPts;
}

MatrixXi &BodySegments::getRightArmLinks() {
	return _rightArmLinks;
}

MatrixXi &BodySegments::getRightArmPts() {
	return _rightArmPts;
}