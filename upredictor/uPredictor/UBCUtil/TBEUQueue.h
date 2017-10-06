#ifndef TB_EU_QUEUE_H
#define TB_EU_QUEUE_H

#include <WinSock2.h>
#include <Windows.h>

#include "ExternalUpdate.h"
#include "ExternalUpdateCollection.h"
#include "ExternalUpdateThread.h"
#include "LameLock.h"
//#include "PipelineProcess.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <concurrent_queue.h>
#include <queue>

using namespace std;

template <typename T> class TBEUQueue :
	public ExternalUpdate
	, public TypeBroadcaster<T>
	, public TypeRecipient<T>
	, public ExternalUpdateCollection
	, public TypeBroadcaster<long>
{
protected:
	//concurrency::concurrent_queue<T> _q;
	queue<T> _q;
	bool _running;
	long _lastUpdateSize;
	ExternalUpdateThread _eut;
	HANDLE
		//_mutex
		_sema;
	LameLock _mutex;

public:
	TBEUQueue() :
		_running(false)
		, _lastUpdateSize(-1)
		, _eut(*this)
	{
		//_mutex = CreateMutex(NULL, FALSE, NULL);
		_sema = CreateSemaphore(NULL, 0, INT_MAX, NULL);
	}

	~TBEUQueue() {
		//CloseHandle(_mutex);
		CloseHandle(_sema);
	}

	//TypeBroadcaster<T>::TypeRecipient
	void processType(T t) {
		//WaitForSingleObject(_mutex, INFINITE);
		_mutex.lock("TBEUQueue::processType");
		ReleaseSemaphore(_sema, 1, NULL);
		_q.push(t);
		//ReleaseMutex(_mutex);
		_mutex.unlock();
	}

	void start() {
		if (!_running) {
			_running = true;
			onStartup();
			_eut.start();
		}
	}

	void stop() {
		_running = false;
		_eut.stop();
	}

	//ExternalUpdate
	void ExternalUpdate::update() {
		WaitForSingleObject(_sema, INFINITE);
		//WaitForSingleObject(_mutex, INFINITE);
		_mutex.lock("TBEUQueue::update");
		long s = _q.size();
		T t = _q.front();
		_q.pop();
		_mutex.unlock();
		//ReleaseMutex(_mutex);

		TypeBroadcaster<T>::fireUpdate(t);
		ExternalUpdateCollection::update();

		if (s != _lastUpdateSize) {
			_lastUpdateSize = s;
			TypeBroadcaster<long>::fireUpdate(s);
		}
	}

	bool hasFutureUpdates() {
		return _running || (!_q.empty());
	}

	void onStartup() {
		ExternalUpdateCollection::onStartup();
		//TypeBroadcaster<T>::onStartup();
		//for (vector<ExternalUpdate *>::iterator iter = _eu.begin(); iter != _eu.end(); iter++)
		//	(*iter)->onStartup();
		//_eut.onStartup();
	}

};

#endif