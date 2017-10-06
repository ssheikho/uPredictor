#ifndef BODY_SEGMENTS_H
#define BODY_SEGMENTS_H

#include <WinSock2.h>
#include <Kinect.h>

#include <Eigen\core>

using namespace Eigen;

class BodyCopy;

class BodySegments {
public:
	enum BSSegments {
		BS_SPINEBASE_SPINEMID,
		BS_SPINEMID_SPINESHOULDER,
		BS_SPINESHOULDER_NECK,
		BS_NECK_HEAD,
		BS_SPINESHOULDER_SHOULDERL,
		BS_SPINESHOULDER_SHOULDERR,
		BS_SHOULDERL_ELBOWL,
		BS_SHOULDERR_ELBOWR,
		BS_ELBOWL_WRISTL,
		BS_ELBOWR_WRISTR,
		BS_WRISTL_HANDL,
		BS_WRISTR_HANDR,
		BS_HANDL_HANDTIPL,
		BS_HANDR_HANDTIPR,
		BS_HANDL_THUMBL,
		BS_HANDR_THUMBR,
		BS_SPINEBASE_HIPL,
		BS_SPINEBASE_HIPR,
		BS_HIPL_KNEEL,
		BS_HIPR_KNEER,
		BS_KNEEL_ANKLEL,
		BS_KNEER_ANKLER,
		BS_ANKLEL_FOOTL,
		BS_ANKLER_FOOTR,
		BS_SEGMENT_COUNT
	};

	enum BSMatTypes {
		BS_ALL,
		BS_RIGHT_ARM,
		BS_MAT_COUNT
	};

	BodySegments();
	~BodySegments();

	MatrixXi &getLinks(BodySegments::BSMatTypes seg);
	MatrixXi &getPts(BodySegments::BSMatTypes seg);
	MatrixXi &getAllLinks();
	MatrixXi &getAllPts();
	MatrixXi &getRightArmLinks();
	MatrixXi &getRightArmPts();

protected:
	//Enumerated segment name across cols, rows are the two links
	MatrixXi
		_allLinks, _allPts
		, _rightArmLinks, _rightArmPts;

	MatrixXi
		*_linkMats[BS_MAT_COUNT]
		, *_ptMats[BS_MAT_COUNT];
};

#endif