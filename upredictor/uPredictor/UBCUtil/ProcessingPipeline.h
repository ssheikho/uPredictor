#ifndef KINECT_PROCESSING_PIPELINE_H
#define KINECT_PROCESSING_PIPELINE_H

#include <WinSock2.h>
#include <Windows.h>

#include "Allocator.h"
#include "ExternalUpdateThread.h"
#include "ProcessPipelineCounter.h"
#include "ProcessPipelineExec.h"
#include "TBEUQueue.h"
#include "TypeRecipientBroadcaster.h"

#include <queue>
#include <vector>

using namespace std;

template<typename T> class ProcessingPipeline :
	public TypeRecipientBroadcaster<T>
{

protected:
	UBC::Allocator<T> &_alloc;
	queue<ProcessPipelineCounter<T> *> _ppc;

	vector<ProcessPipelineExec<T> *> _ppe;
	vector<TBEUQueue<ProcessPipelineCounter<T> *> *> _q;
	HANDLE _mutex;// , _sema;

	void allocatePPC() {
		_ppc.push(new ProcessPipelineCounter<T>(this, _alloc.getInstance()));
	}
	
	ProcessPipelineCounter<T> *getPPC() {
		ProcessPipelineCounter<T> *ppc = NULL;

		if (_ppc.size()) {
			ppc = _ppc.front();
			_ppc.pop();
		}
		else {
			ppc = new ProcessPipelineCounter<T>(this, _alloc.getInstance());
		}

		return ppc;
	}

public:
	const int _nThreads;

	ProcessingPipeline(UBC::Allocator<T> &alloc) :
		_alloc(alloc), _nThreads(0) {
		_mutex = CreateMutex(NULL, FALSE, NULL);
		//_sema = CreateSemaphore(NULL, 0, INT_MAX, NULL);
		//for (int i = 0; i < poolDepth; i++) allocatePPC();
		//ReleaseSemaphore(_sema, poolDepth, NULL);
	}

	~ProcessingPipeline() {
		CloseHandle(_mutex);
		//CloseHandle(_sema);
	}

	void addProc(shared_ptr<TypeRecipient> proc) {
		WaitForSingleObject(_mutex, INFINITE);
		ProcessPipelineExec<T> *ppe = new ProcessPipelineExec<T>(proc);
		TBEUQueue<ProcessPipelineCounter<T> *> *q =
			new TBEUQueue<ProcessPipelineCounter<T> *>();
		q->TypeBroadcaster<ProcessPipelineCounter<T> *>::addRecipient(ppe);
		_ppe.push_back(ppe);
		_q.push_back(q);
		(int)_nThreads = _nThreads + 1;
		ReleaseMutex(_mutex);
	}

	void start() {
		WaitForSingleObject(_mutex, INFINITE);
		for (
			vector<TBEUQueue<ProcessPipelineCounter<T> *> *>::iterator iter =
			_q.begin();
			iter != _q.end();
			iter++
			) {
			//onStartup();
			(*iter)->start();
		}
		ReleaseMutex(_mutex);
	}

	void stop() {
		WaitForSingleObject(_mutex, INFINITE);
		for (
			vector<TBEUQueue<ProcessPipelineCounter<T> *> *>::iterator iter =
			_q.begin();
			iter++
			)
			(*iter)->stop();
		ReleaseMutex(_mutex);
	}

	void processType(T t) {
		//WaitForSingleObject(_sema, INFINITE);
		WaitForSingleObject(_mutex, INFINITE);

		ProcessPipelineCounter<T> *ppc = getPPC();
		ppc->setT(t);
		for (
			vector<TBEUQueue<ProcessPipelineCounter<T> *> *>::iterator iter =
			_q.begin();
			iter != _q.end();
			iter++
			) {
			(*iter)->processType(ppc);
		}
		ReleaseMutex(_mutex);
	}

	void onStartup() {
		WaitForSingleObject(_mutex, INFINITE);
		for (
			vector<TBEUQueue<ProcessPipelineCounter<T> *> *>::iterator iter =
			_q.begin();
			iter != _q.end();
			iter++
			) {
			(*iter)->onStartup();
		}

		/*
		for (
			vector<ProcessPipelineExec<T> *>::iterator iter = _ppe.begin();
			iter != _ppe.end(); iter++) {
			(*iter)->onStartup();
		}
		*/

		ReleaseMutex(_mutex);
	}

	void returnCounter(ProcessPipelineCounter<T> *ppc) {
		WaitForSingleObject(_mutex, INFINITE);
		T t = ppc->getT();
		ppc->reset();
		_ppc.push(ppc);
		//ReleaseSemaphore(_sema, 1, NULL);
		ReleaseMutex(_mutex);
		fireUpdate(t);
	}
};

#endif

/*
Class that counts returns from each thread
This class must process what the thread processes
That means that the thread must call the ProcessType on THIS class
and in return THIS class must rereturn itself to the counter queue
Then that method sends down the pipeline.
*/