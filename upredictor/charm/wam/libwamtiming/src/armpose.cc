/*
The armpose class associates 7 joint angles with 
a string name to specify a single WAM pose
*/

#include "armpose.h"

#include <iostream>

using namespace std;

ArmPose::ArmPose() {}
ArmPose::~ArmPose() {}

void ArmPose::printDest() {
	for(int i=0; i < getNAngs(); i++){
		cout << getAng(i) << endl;
	}
}

string ArmPose::getAngString(int joint) {
	ostringstream ss;
	ss << getAng(joint);
	return ss.str();
}

void ArmPose::copyInto(ArmPose &ap) {
	for(int i=0; i < getNAngs(); i++)	ap.setAng(i, getAng(i));
}
