#ifndef PAUSE_H
#define PAUSE_H


#ifdef _WIN32
	#define NOMINMAX
	#include <WinSock2.h>
	#include <Windows.h>
#elif __linux__
	#include <pthread.h>
	#include <semaphore.h>
#endif

#include "IntSwitch.h"

class Pause : public IntSwitch {
public:
	Pause(bool startPaused);
	~Pause();

	void pause();
	void unpause();
	void waitpause();

	//IntSwitch
	void updateSwitch(int val);

protected:
	bool _isPaused;
	int _holdCount;

	#ifdef _WIN32
		HANDLE _sema, _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
		sem_t _sema;
	#endif
};

#endif
