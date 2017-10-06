#ifndef EXTERNAL_QUEUE_PAIR_H
#define EXTERNAL_QUEUE_PAIR_H

#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include "ExternalUpdate.h"
#include "TypeRecipient.h"

template<typename T> class ExternalQueuePair :
	public ExternalUpdate {
public:
	ExternalQueuePair(TypeRecipient<T> *recipient, T val) :
		_recipient(recipient), _val(val), _notDone(true)
		, _sema(CreateSemaphore(NULL, 0, INT_MAX, NULL))
	{}

	~ExternalQueuePair() {}

	void update() {
		_recipient->processType(_val);
		_notDone = false;
		ReleaseSemaphore(_sema, 1, NULL);
	}

	bool hasFutureUpdates() {
		return _notDone;
	}

	void onStartup() {}

	void waitUntilDone() {
		WaitForSingleObject(_sema, INFINITE);
	}

protected:
	TypeRecipient<T> *_recipient;
	T _val;
	bool _notDone;
	HANDLE _sema;
};

#endif