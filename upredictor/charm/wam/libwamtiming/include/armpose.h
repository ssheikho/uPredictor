/*
The armpose class associates 7 joint angles with 
a string name to specify a single WAM pose
*/

#ifndef ARM_POSE_H
#define ARM_POSE_H

#include <sstream>
#include <string>

using namespace std;

class PosList;

class ArmPose {
	public:
		ArmPose();
		~ArmPose();

		void printDest();
		string getAngString(int joint);
		void copyInto(ArmPose &ap);

		virtual string getName() = 0;
		virtual void setName(string name) = 0;
		virtual int getNAngs() = 0;
		virtual float getAng(int joint) = 0;
		virtual void setAng(int joint, float val) = 0;
};

#endif
