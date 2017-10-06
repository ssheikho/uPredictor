#ifndef PRINT_ARM_POSER_H
#define PRINT_ARM_POSER_H

#include "armposer.h"

class PrintArmPoser : public ArmPoser {
	public:
		PrintArmPoser(int nAngs);
		~PrintArmPoser();

		void updatePose(ArmPose *pose);
		void idle();

		//Inherited from ArmPose
		string getName();
		void setName(string name);
		int getNAngs();
		float getAng(int joint);
		void setAng(int joint, float val);

	protected:
		string _name;
		int _nAngs;
		float *_angs;
};

#endif
