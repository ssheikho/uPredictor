#include "RefCounter.h"

#include <cstdlib>

RefCounter::RefCounter(void *val) :
	_count(0)
	, _val(val) {
	pthread_mutex_init(&_mutex, NULL);
}

RefCounter::~RefCounter() {}

void RefCounter::incr(string lockHolder) {
	pthread_mutex_lock(&_mutex);

	_count++;

	pthread_mutex_unlock(&_mutex);
}

void RefCounter::decr(string lockHolder, RefCountManager *rcm) {
	pthread_mutex_lock(&_mutex);

	_count--;
	if ((_count == 0) && (rcm)) rcm->returnRC(this);
	if (_count < 0) abort();

	pthread_mutex_unlock(&_mutex);
}

void *RefCounter::getVal() {
	pthread_mutex_lock(&_mutex);

	void *val = _val;

	pthread_mutex_unlock(&_mutex);

	return val;
}

void RefCounter::reset() {
	_count = 0;
	//abort();
}
