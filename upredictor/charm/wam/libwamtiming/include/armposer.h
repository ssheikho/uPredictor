#ifndef ARM_POSER_H
#define ARM_POSER_H

#include "armpose.h"
#include "armposelistener.h"

#include <vector>

using namespace std;

class ArmPoser : public ArmPose, public ArmPoseListener {
	public:
		ArmPoser();
		~ArmPoser();

		virtual void idle() = 0;

		void addListener(ArmPoseListener *l);

	protected:
		void fireUpdate(ArmPose *pose);

		vector<ArmPoseListener *> _l;
};

#endif
