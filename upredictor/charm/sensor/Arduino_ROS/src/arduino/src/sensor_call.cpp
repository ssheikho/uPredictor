#include <stdio.h>		//Standard input/output definitions
#include <string.h>		//String function definitions
#include <unistd.h>		//UNIX standard function definitions
#include <fcntl.h>		//File control definitions
#include <errno.h>		//Error number definitions
#include <termios.h>		//POSIX terminal control definitions
#include <iostream>		//Input-Output Streams

#include "ros/ros.h"
#include "arduino/TestService.h"
#include "std_msgs/Int32MultiArray.h"
#include "arduino/table_state.h"
#include <cstdlib>

using namespace std;

char *portname = "/dev/ttyACM0";
char incomingData[30];	
char wholeRequest[] = "0";		
int nSensor = 30;
arduino::table_state current_table;

bool isConnectionOpen(int fd) {

	return fcntl(fd, F_GETFD) >= 0; 		// simple file operation to check connection
}

void convertToTableState(std_msgs::Int32MultiArray sd) {

	int sensor_count = 0;

	for (int i = 0; i < 18; i++) {

		if (i < 6) {
			current_table.bolt_holes[i].block_num = i+1;
			current_table.bolt_holes[i].top_sensor = sd.data[sensor_count];
                        sensor_count++;
			current_table.bolt_holes[i].middle_sensor = sd.data[sensor_count];
			sensor_count++;
			current_table.bolt_holes[i].bottom_sensor = sd.data[sensor_count];
			sensor_count++;
		}

		if (i >= 6) {
			if (i % 2) {
				current_table.rack_holes[((i+7)/2)-1].rack_num = (i+7)/2;
				current_table.rack_holes[((i+7)/2)-1].sensor = sd.data[sensor_count]; 
				sensor_count++;
			}
			else {
				current_table.rack_holes[((i-4)/2)-1].rack_num = (i-4)/2;
				current_table.rack_holes[((i-4)/2)-1].sensor = sd.data[sensor_count]; 
				sensor_count++;
			}
		}
	}
}

int main(int argc, char* argv[]) {

	int count = 0;
	int fd;
	fd = open(portname, O_RDWR | O_NOCTTY);

	struct termios options;

 	tcgetattr(fd, &options);
 
	/* 9600 baud */
 	cfsetispeed(&options, B9600);
 	cfsetospeed(&options, B9600);

	/* No parity */
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	options.c_cflag |= (CLOCAL | CREAD);

	options.c_cc[VMIN] = 30;   // wait for 30 bytes before reading
 	options.c_cc[VTIME] = 0;

	tcsetattr(fd, TCSANOW, &options);

	/* Wait for reset and flush*/
 	usleep(1000*1000);	  
 	tcflush(fd, TCIOFLUSH);
	
	std_msgs::Int32MultiArray sensor_data;
	std_msgs::Int32MultiArray old_data;	

	ros::init(argc, argv, "sensor_call");

  	ros::NodeHandle n;
 	ros::ServiceClient client = n.serviceClient<arduino::TestService>("sensor_request");
 	arduino::TestService srv; 		// to be replaced with Justin's planner service

	while (isConnectionOpen(fd)) {
	
		old_data.data = sensor_data.data;
		sensor_data.data.clear();

		write(fd, wholeRequest, 1); 	// send request for current board state
		read(fd, incomingData, 30);
		
		for (int i = 0; i < nSensor; i++) {
			sensor_data.data.push_back((int)incomingData[i]);
		}

		for (int j = 0; j < nSensor; j++) {
			if ((count == 0) || (old_data.data[j] != sensor_data.data[j])) {		
				convertToTableState(sensor_data);
 				srv.request.status = current_table; 
				if (client.call(srv)) {
 	   				ROS_INFO("Service call successful!");
 				} else {
  	  				ROS_ERROR("Failed to call service sensor_request");
  	 				return 1;
 				}
				break;
			}
		}

		count++;

		// usleep(1000*1000); 		// for easy reading

	}
	
	close(fd);
			

	return 0;
}

