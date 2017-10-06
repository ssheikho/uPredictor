#define NOMINMAX
#include <Windows.h>

#include "CUDAControl.h"

extern "C" {
	typedef void(CALLBACK* setupCUDAType)(void);
	typedef int(CALLBACK* setDeviceType)(void);
}

void setupCUDA(HINSTANCE hinstDLL) {
	setupCUDAType setupCUDA =
		(setupCUDAType)GetProcAddress(hinstDLL, "setupCUDA");
	setupCUDA();
}

/*
int setDevice(HINSTANCE hinstDLL) {
	setDeviceType setDevice =
		(setDeviceType)GetProcAddress(hinstDLL, "setDevice");
	return setDevice();
}
*/