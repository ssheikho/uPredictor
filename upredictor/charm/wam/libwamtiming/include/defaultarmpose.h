#ifndef DEFAULT_ARM_POSE_H
#define DEFAULT_ARM_POSE_H

#include "armpose.h"

#include <sstream>
#include <string>

using namespace std;

class PosList;

class DefaultArmPose : public ArmPose {
	public:

		DefaultArmPose(PosList *pg, string name, float *jointAngles, int nAngs);
		~DefaultArmPose();

		string getName();
		void setName(string name);
		int getNAngs();
		float getAng(int joint);
		string getAngString(int joint);
		void setAng(int joint, float val);
	

	protected:
		PosList *_pg;
		string _name;
		int _nAngs;
		float *_jointAngles;
};

#endif
