#include "ViconData.h"

ViconData::ViconData() {}
ViconData::~ViconData() {}

ViconJoints &ViconData::getVJ() {
	return _vj;
}

ViconTrajectories &ViconData::getVT() {
	return _vt;
}
