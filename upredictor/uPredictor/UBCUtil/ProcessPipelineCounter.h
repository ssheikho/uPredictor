#ifndef PROCESS_PIPELINE_COUNTER_H
#define PROCESS_PIPELINE_COUNTER_H

#include <WinSock2.h>
#include <Windows.h>

#include "TypeRecipient.h"

template<typename T> class ProcessingPipeline;

template<typename T> class ProcessPipelineCounter {
protected:
	ProcessingPipeline<T> *_pp;
	T _t;
	int _ct;
	HANDLE _mutex;

public:
	ProcessPipelineCounter(ProcessingPipeline<T> *pp, T t) :
		_pp(pp)
		, _t(t)
		, _ct(0)
	{
		_mutex = CreateMutex(NULL, FALSE, NULL);
	}

	~ProcessPipelineCounter() {
		CloseHandle(_mutex);
	}

	void runProc(shared_ptr<TypeRecipient<T>> proc) {
		WaitForSingleObject(_mutex, INFINITE);
		proc->processType(_t);
		_ct++;
		if (_ct == _pp->_nThreads)
			_pp->returnCounter(this);
		ReleaseMutex(_mutex);
	}

	void reset() {
		WaitForSingleObject(_mutex, INFINITE);
		//T t;
		//_t = t;
		_ct = 0;
		ReleaseMutex(_mutex);
	}

	void setT(T t) {
		WaitForSingleObject(_mutex, INFINITE);
		_t = t;
		ReleaseMutex(_mutex);
	}

	T getT() {
		WaitForSingleObject(_mutex, INFINITE);
		T t = _t;
		ReleaseMutex(_mutex);
		return t;
	}

};

#endif