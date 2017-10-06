#ifndef EXTERNAL_UPDATE_THREAD_H
#define EXTERNAL_UPDATE_THREAD_H

#include <WinSock2.h>
#include <Windows.h>

#include "ExternalUpdate.h"

static DWORD WINAPI eutThread(LPVOID lpParam);

class ExternalUpdateThread : public ExternalUpdate {
public:
	ExternalUpdateThread(ExternalUpdate &eu);
	~ExternalUpdateThread();

	void start();
	void stop();

	void update();

	bool hasFutureUpdates();

protected:
	ExternalUpdate &_eu;
	bool _started;
	HANDLE _thread;
};

#endif