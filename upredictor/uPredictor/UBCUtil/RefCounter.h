#ifndef REF_COUNTER_H
#define REF_COUNTER_H

#ifdef _WIN32
	#define NOMINMAX
	#include <WinSock2.h>
	#include <Windows.h>
#elif __linux__
	#include <pthread.h>
	#include <semaphore.h>
#endif

#include <string>
#include <vector>

using namespace std;

class RefCounter {
protected:
	long _count;
	void *_val;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif

public:
	class RefCountManager {
	public:
		virtual void returnRC(RefCounter *rc) = 0;
	};

	RefCounter(void *val);
	~RefCounter();

	void incr(string lockHolder);
	void decr(string lockHolder, RefCountManager *rcm);
	void *getVal();
	void reset();

};

#endif
