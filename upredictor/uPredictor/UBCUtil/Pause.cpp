#include "Pause.h"

Pause::Pause(bool startPaused) :
	_isPaused(startPaused),
	_holdCount(0) {
	#ifdef _WIN32
		_sema = CreateSemaphore(NULL, 0, INT_MAX, NULL);
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#elif __linux__
		sem_init(&_sema, 0, 0);
		pthread_mutex_init(&_mutex, NULL);
	#endif
}

Pause::~Pause() {}

void Pause::pause() {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif

	_isPaused = true;

	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif
}

void Pause::unpause() {
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
		_isPaused = false;
		ReleaseSemaphore(_sema, _holdCount, NULL);
		_holdCount = 0;
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
		_isPaused = false;
		while(_holdCount > 0) {
			sem_post(&_sema);
			_holdCount--;
		}
		pthread_mutex_unlock(&_mutex);
	#endif
}

void Pause::waitpause() {
	bool willPause = false;
	#ifdef _WIN32
		WaitForSingleObject(_mutex, INFINITE);
	#elif __linux__
		pthread_mutex_lock(&_mutex);
	#endif
	if (willPause = _isPaused) {
		_holdCount++;
	}
	#ifdef _WIN32
		ReleaseMutex(_mutex);
	#elif __linux__
		pthread_mutex_unlock(&_mutex);
	#endif

	if(willPause) {
		#ifdef _WIN32
			WaitForSingleObject(_mutex, INFINITE);
		#elif __linux__
			pthread_mutex_lock(&_mutex);
		#endif
	}
}

void Pause::updateSwitch(int val) {
	switch (val) {
	case 0:
		pause();
		break;
	case 1:
		unpause();
		break;
	}
}
