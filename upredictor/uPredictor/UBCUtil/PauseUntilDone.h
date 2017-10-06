#ifndef PAUSE_UNTIL_DONE_H
#define PAUSE_UNTIL_DONE_H

#include <WinSock2.h>
#include <Windows.h>

#include "IntSwitch.h"

template <typename T> class PauseUntilDone :
	public TypeRecipient<T>
	, public IntSwitch {
public:
	PauseUntilDone() : _pause(false) {
		_sema = CreateSemaphore(NULL, 0, INT_MAX, NULL);
	}

	~PauseUntilDone() {
		CloseHandle(_sema);
	}

	void wait() {
		if (_pause) {
			WaitForSingleObject(_sema, 50);
		}
	}


	void processType(T t) {
		if (_pause) ReleaseSemaphore(_sema, 1, NULL);
	}

	void onStartup() {}

	void updateSwitch(int val) {
		switch (val) {
		case 0:
			_pause = true;
			break;
		case 1:
			_pause = false;
			break;
		case 2:
			ReleaseSemaphore(_sema, 1, NULL);
			break;
		}
	}

protected:
	HANDLE _sema;
	bool _pause;
};

#endif
