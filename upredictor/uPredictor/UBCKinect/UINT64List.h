#ifndef UINT64_LIST_H
#define UINT64_LIST_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include "FakeWindowsTypes.h"
#endif

class UINT64List {
public:
	virtual size_t nUINT64s() = 0;
	virtual UINT64 getUINT64(size_t index) = 0;
};

#endif
