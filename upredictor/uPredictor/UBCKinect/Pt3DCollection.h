#ifndef PT_3D_COLLECTION_H
#define PT_3D_COLLECTION_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#include <pthread.h>
#include <semaphore.h>
#endif

class Pt3DCollection {
public:
	virtual int getNPts() = 0;
	virtual CameraSpacePoint *getCameraPt(int index) = 0;
	virtual CameraSpacePoint *getCameraPts() = 0;
	virtual unsigned char *getRGB() = 0;
};

#endif
