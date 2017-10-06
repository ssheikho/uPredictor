#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.msg"
#include "trajectory_msgs/JointTrajectoryPoint.msg"

int main(int argc, char **argv)
{
	// Setup ROS
	ros::init(argc, argv, "trajectoryPublisher");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<trajectory_msgs::JointTrajectory>("/wam/arm_trajectory_controller/command", 1000);

	// Create message
	trajectory_msgs::JointTrajectory msg;

	msg.joint_names.resize(7);

	msg.joint_names.push_back("wam/base_yaw_joint");
	msg.joint_names.push_back("wam/shoulder_pitch_joint");
	msg.joint_names.push_back("wam/shoulder_yaw_joint");
	msg.joint_names.push_back("wam/elbow_pitch_joint");
	msg.joint_names.push_back("wam/wrist_yaw_joint");
	msg.joint_names.push_back("wam/wrist_pitch_joint");
	msg.joint_names.push_back("wam/palm_yaw_joint"];

	msg.points.resize(INTERPCOUNT);

	//Interpolation goes here
	for (int i = 0; i < INTERPCOUNT; i++) {

		trajectory_msgs::JointTrajectoryPoint p;

		p.points[i].positions.resize(7);

		p.points[i].positions[0] = ;
		p.points[i].positions[1] = ;
		p.points[i].positions[2] = ;
		p.points[i].positions[3] = ;
		p.points[i].positions[4] = ;
		p.points[i].positions[5] = ;
		p.points[i].positions[6] = ;

		p.points[i].velocities.resize(7);

		for (int j = 0; j < 7; j++) {
			p.points[i].velocities[j] = 0.0;
		}

		p.time_from_start = ;

		msg.points.push_back(p);

	}



	// Publish message
	pub.publish(msg);

	ros::spin();


	return 0;
}

