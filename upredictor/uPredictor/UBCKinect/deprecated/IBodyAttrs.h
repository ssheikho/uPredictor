#ifndef IBODY_ATTRS_H
#define IBODY_ATTRS_H

#include <WinSock2.h>
#include <Kinect.h>

struct IBodyAttrs {
	BOOLEAN _isTracked;
	Joint _joints[JointType_Count];
	JointOrientation _orientations[JointType_Count];
	UINT64 _trackingID;
};

#endif