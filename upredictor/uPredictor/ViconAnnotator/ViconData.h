#ifndef VICON_DATA_H
#define VICON_DATA_H

#include "ViconJoints.h"
#include "ViconTrajectories.h"

class ViconData {
public:
	ViconData();
	~ViconData();

	ViconJoints &getVJ();
	ViconTrajectories &getVT();

protected:
	ViconJoints _vj;
	ViconTrajectories _vt;
};

#endif
