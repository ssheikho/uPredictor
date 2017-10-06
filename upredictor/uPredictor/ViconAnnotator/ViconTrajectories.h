#ifndef VICON_TRAJECTORIES_H
#define VICON_TRAJECTORIES_H

#include "NameCrossIndex.h"
#include "ViconDefs.h"

#include <map>
#include <string>

class ViconTrajectories {
public:
	ViconTrajectories();
	~ViconTrajectories();

	void setLabels(std::string labelsLine);

	NameCrossIndex &getNCI();

protected:
	NameCrossIndex _nci;
	//map<>
};

#endif
