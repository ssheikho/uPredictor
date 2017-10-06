#include "armposer.h"

ArmPoser::ArmPoser() {}
ArmPoser::~ArmPoser() {}

void ArmPoser::addListener(ArmPoseListener *l) {
	_l.push_back(l);
}

void ArmPoser::fireUpdate(ArmPose *pose) {
	for(int i = 0; i < _l.size(); i++)
		_l[i]->updatePose(pose);
}
