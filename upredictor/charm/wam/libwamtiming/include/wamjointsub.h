#ifndef WAM_JOINT_SUB_H
#define WAM_JOINT_SUB_H

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

class WAMJointSub {
	public:
		WAMJointSub(ros::NodeHandle &nh);
		~WAMJointSub();
	
		static void jointSubCB(const sensor_msgs::JointState &msg);

	protected:
		
};

#endif
