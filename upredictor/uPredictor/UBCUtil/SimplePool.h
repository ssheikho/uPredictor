#ifndef SIMPLE_POOL_H
#define SIMPLE_POOL_H

#ifdef _WIN32
#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>
#elif __linux__
#include <pthread.h>
#endif

#include "Allocator.h"
#include "RefCountedPtr.h"
#include "RefCounter.h"
#include "TypeBroadcaster.h"
#include "TypeFactory.h"

#include <queue>

using namespace std;

template<typename T> class SimplePool :
	public TypeBroadcaster<long>,
	protected RefCounter::RefCountManager
{
private:
	queue<RefCounter *> _q;

	#ifdef _WIN32
		HANDLE _mutex;
	#elif __linux__
		pthread_mutex_t _mutex;
	#endif

	TypeFactory<T> &_f;
	int _poolDepth, _maxDepth;

protected:
	void returnRC(RefCounter *q) {
		pthread_mutex_lock(&_mutex);

		long s = _q.size();
		q->reset();
		_q.push(q);

		pthread_mutex_unlock(&_mutex);

		fireUpdate(s + 1);
	}

public:
	class PooledPtr {
		//This probably needs a mutex
	protected:
		RefCounter *_rc;
		SimplePool *_sp;

		#ifdef _WIN32
			HANDLE _pooledPointerMut;
		#elif __linux__
			pthread_mutex_t _pooledPointerMut;
		#endif

	public:
		operator bool() const {
			#ifdef _WIN32
				WaitForSingleObject(_pooledPointerMut, INFINITE);
			#elif __linux__
				pthread_mutex_lock(&_pooledPointerMut);
			#endif

			bool retVal = _rc != NULL;

			#ifdef _WIN32
				ReleaseMutex(_pooledPointerMut);
			#elif __linux__
				pthread_mutex_unlock(&_pooledPointerMut);
			#endif

			return retVal;
		}

	private:
		void incr(string s) {
			if (_rc) _rc->incr(s);
		}

		void decr(string s) {
			if (_rc) _rc->decr(s, _sp);
		}

	public:
		PooledPtr(SimplePool *sp, RefCounter *rc = NULL) {
			pthread_mutex_init(&_pooledPointerMut, NULL);
			pthread_mutex_lock(&_pooledPointerMut);

			_rc = rc;
			_sp = sp;
			incr("PooledPtr(SimplePool *sp, RefCounter *rc = NULL)");

			pthread_mutex_unlock(&_pooledPointerMut);
		}

		PooledPtr(const PooledPtr &p) {
			pthread_mutex_init(&_pooledPointerMut, NULL);
			pthread_mutex_lock(&_pooledPointerMut);

			if (p._rc) {
				_rc = p._rc;
				_sp = p._sp;
				incr("PooledPtr(const PooledPtr &p)");
			}
			else {
				_rc = NULL;
				_sp = NULL;
			}

			pthread_mutex_unlock(&_pooledPointerMut);
		}

		~PooledPtr() {
			pthread_mutex_lock(&_pooledPointerMut);

			decr("~PooledPtr()");

			pthread_mutex_unlock(&_pooledPointerMut);
			pthread_mutex_destroy(&_pooledPointerMut);
		}

		T &operator*()
		{
			T *t = NULL;

			pthread_mutex_lock(&_pooledPointerMut);
			t = (T *)(_rc ? _rc->getVal() : NULL);
			pthread_mutex_unlock(&_pooledPointerMut);

			return *t;
		}

		T *operator->() {
			T *t = NULL;

			pthread_mutex_lock(&_pooledPointerMut);
			t = (T *)(_rc ? _rc->getVal() : NULL);
			pthread_mutex_unlock(&_pooledPointerMut);

			return t;
		}

		//BE SMART! This returns a pointer that is NOT counted.
		T *get() {
			T *t = NULL;
			t = (T *)(_rc ? _rc->getVal() : NULL);
			return t;
		}

		PooledPtr &operator=(const PooledPtr &p) {
			pthread_mutex_lock(&_pooledPointerMut);
			pthread_mutex_lock((pthread_mutex_t *)&p._pooledPointerMut);

			if (this != &p) {
				decr("&operator=");
				_rc = p._rc;
				_sp = p._sp;
				incr("&operator=");
				//PooledPtr &retVal = *this;
			}

			pthread_mutex_unlock(&_pooledPointerMut);
			pthread_mutex_unlock((pthread_mutex_t *)&p._pooledPointerMut);

			return *this;
		}
	};

	SimplePool(TypeFactory<T> &f, int maxDepth = -1) :
		_f(f)
		, _poolDepth(0)
		, _maxDepth(maxDepth)
		, _alloc(this) {
		pthread_mutex_init(&_mutex, NULL);
	}

	~SimplePool() {
		pthread_mutex_destroy(&_mutex);
	}

	PooledPtr getInstance() {
		RefCounter *rc = NULL;

		pthread_mutex_lock(&_mutex);

		long s = _q.size();
		if (s == 0) {
			rc = new RefCounter(_f.getInstance());
			_poolDepth++;
		}
		else {
			rc = _q.front();
			_q.pop();
		}

		pthread_mutex_unlock(&_mutex);

		return PooledPtr(this, rc);
	}

	long poolSize() {
		pthread_mutex_lock(&_mutex);
		long s = _q.size();
		pthread_mutex_unlock(&_mutex);
		return s;
	}


	long poolDepth() {
		pthread_mutex_lock(&_mutex);
		long s = _poolDepth;
		pthread_mutex_unlock(&_mutex);

		return s;
	}

	UBC::Allocator<PooledPtr> &getAllocator() {
		return _alloc;
	}

	protected:

	class SPAlloc : public UBC::Allocator<PooledPtr> {
	public:
		SPAlloc(SimplePool *sp) : _sp(sp) {}

		~SPAlloc() {}

		PooledPtr getInstance() {
			return _sp->getInstance();
		}

	protected:
		SimplePool *_sp;
	};

	void addToPool() {
		_q.push(new RefCounter(_f.getInstance()));
		//ReleaseSemaphore(_sema, 1, NULL);
	}

	SPAlloc _alloc;
};

#endif
