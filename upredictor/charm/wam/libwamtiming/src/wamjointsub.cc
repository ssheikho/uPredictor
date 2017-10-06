#include "wamjointsub.h
#include <ros/ros.h>

WAMJointSub::WAMJointSub() {
	ros::Subscriber sub = nh.subscribe("/wam/joint_states", 1, jointSubCB);
}

WAMJointSub::~WAMJointSub() {}

void WAMJointSub::jointSubCB(const sensor_msgs::JointState &msg) {
	
}
