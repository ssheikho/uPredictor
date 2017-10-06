#include <stdio.h>		//Standard input/output definitions
#include <string.h>		//String function definitions
#include <unistd.h>		//UNIX standard function definitions
#include <fcntl.h>		//File control definitions
#include <errno.h>		//Error number definitions
#include <termios.h>		//POSIX terminal control definitions
#include <iostream>		//Input-Output Streams

#include "ros/ros.h"
#include "arduino/TestService.h"

using namespace std;

bool status(arduino::TestService::Request  &req, arduino::TestService::Response &res) {

  	res.result = req.status;

	for (int i = 0; i < 6; i++) {
		ROS_INFO("Block #: %d.", res.result.bolt_holes[i].block_num);
		ROS_INFO("top_sensor: %s ", res.result.bolt_holes[i].top_sensor ? "closed" : "open");
		ROS_INFO("middle_sensor: %s ", res.result.bolt_holes[i].middle_sensor ? "closed" : "open");
		ROS_INFO("bottom_sensor: %s ", res.result.bolt_holes[i].bottom_sensor ? "closed" : "open");
	}

	for (int i = 0; i < 12; i++) {
		ROS_INFO("Rack #: %d", res.result.rack_holes[i].rack_num);
		ROS_INFO("sensor: %s ", res.result.rack_holes[i].sensor ? "closed" : "open");
	}

	return true;
}

int main(int argc, char* argv[]) {

	ros::init(argc, argv, "testservice");
 	ros::NodeHandle n;
	
	ros::ServiceServer service = n.advertiseService("sensor_request", status);
  	ros::spin();

	return 0;
}
