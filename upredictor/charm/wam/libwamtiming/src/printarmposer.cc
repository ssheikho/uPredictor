#include "printarmposer.h"
#include "armpose.h"

#include <cstdlib>
#include <iostream>

PrintArmPoser::PrintArmPoser(int nAngs) : _name("Current Pose"),
	_nAngs(nAngs), _angs(new float[_nAngs]) {}

PrintArmPoser::~PrintArmPoser() {
	delete[] _angs;
}

void PrintArmPoser::updatePose(ArmPose *pose) {
	cout << pose->getName() << ":	";
	for(int i = 0; i < pose->getNAngs(); i++) {
		double d = pose->getAng(i);
		_angs[i] = d;
		cout << d << "	";
	}
	cout << endl;

	fireUpdate(pose);
}

void PrintArmPoser::idle() {
	cout << "IDLING ARM" << endl;
}

string PrintArmPoser::getName() 					{	return _name;	}
void PrintArmPoser::setName(string name)			{	_name = name;	}
int PrintArmPoser::getNAngs()						{	return _nAngs;	}

float PrintArmPoser::getAng(int joint)				{
	return _angs[joint];
}

void PrintArmPoser::setAng(int joint, float val)	{
	_angs[joint] = val;
}
