#include "defaultarmpose.h"
#include "poslist.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

DefaultArmPose::DefaultArmPose(PosList *pg, string name,
	float *jointAngles, int nAngs) :
	_pg(pg), _name(name), _nAngs(nAngs), _jointAngles(new float[_nAngs]) {
	memcpy(_jointAngles, jointAngles, sizeof(float) * _nAngs);
	_pg->addPose(this);
}

DefaultArmPose::~DefaultArmPose() {}

string DefaultArmPose::getName() {
	return _name;
}

void DefaultArmPose::setName(string name) {
	_name = name;
}

int DefaultArmPose::getNAngs() {
	return _nAngs;
}

float DefaultArmPose::getAng(int joint) {
	return _jointAngles[joint];
}

void DefaultArmPose::setAng(int joint, float val) {
	_jointAngles[joint] = val;
}
