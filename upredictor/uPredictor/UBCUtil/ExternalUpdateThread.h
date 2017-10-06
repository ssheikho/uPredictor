#ifndef EXTERNAL_UPDATE_THREAD_H
#define EXTERNAL_UPDATE_THREAD_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#elif __linux__
#include <pthread.h>
#endif

#include "ExternalUpdate.h"

#ifdef _WIN32
static DWORD WINAPI eutThread(LPVOID lpParam);
#elif __linux__
#include <pthread.h>
void *eutThread(void *lpParam);
#endif

class ExternalUpdateThread : public ExternalUpdate {
public:
	ExternalUpdateThread(ExternalUpdate &eu);
	~ExternalUpdateThread();

	void start();
	void stop();

	void update();
	bool hasFutureUpdates();
	void onStartup();

protected:
	ExternalUpdate &_eu;
	bool _started;

#ifdef _WIN32
	HANDLE _thread;
#elif __linux__
	pthread_t _thread;
#endif
};

#endif
