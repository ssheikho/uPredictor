#include <stdio.h>		//Standard input/output definitions
#include <string.h>		//String function definitions
#include <unistd.h>		//UNIX standard function definitions
#include <fcntl.h>		//File control definitions
#include <errno.h>		//Error number definitions
#include <termios.h>		//POSIX terminal control definitions
#include <iostream>		//Input-Output Streams

using namespace std;


char *portname = "/dev/ttyACM0";
char incomingData[30];	
char wholeRequest[] = "0";		
int nSensor = 30;

bool isConnectionOpen(int fd) {

	return fcntl(fd, F_GETFD) >= 0; 		// simple file operation, true means file is still open
}

bool isHoleOpen(int holeNum) {
     if (incomingData != NULL) {
         if ((int)incomingData[holeNum] == 0) {
	    cout << "Hole " << holeNum << " is open!" << endl;
	    return true;
	    }
         else {
	    cout << "Hole " << holeNum << " is closed!" << endl;
	    return false;
	    }
     }
}

int main(int argc, char* argv[]) {

	int bytesRead = 0;
	int bytesWritten = 0;
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

	while (isConnectionOpen(fd)) {

		bytesWritten = write(fd, wholeRequest, 1); 		// send request for board state

		bytesRead = read(fd, incomingData, 30);

		cout << "SENSOR DATA:" << endl;
		for (int i = 0; i < nSensor; i++)
			cout << "	[" << i << "]" << (int)incomingData[i] << endl;
		
		/*isHoleOpen(0);
		isHoleOpen(1);
		isHoleOpen(2);
		isHoleOpen(3);
		isHoleOpen(4);
		isHoleOpen(5);*/

		usleep(1000*1000);

		}			

	close(fd);

	return 0;
}
