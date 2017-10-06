#ifndef ARM_POSE_LISTENER_H
#define ARM_POSE_LISTENER_H

class ArmPose;

class ArmPoseListener {
	public:
		ArmPoseListener();
		~ArmPoseListener();

		virtual void updatePose(ArmPose *pose) = 0;
};

#endif
