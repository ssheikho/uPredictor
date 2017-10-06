#ifndef REF_COUNTED_PTR_H
#define REF_COUNTED_PTR_H

#include "RefCounter.h"

template <typename T> class RefCountedPtr {
protected:
	RefCounter *_rc;

	RefCountedPtr(RefCounter *rc) : _rc(rc) {}

public:
	virtual void onCountZero() = 0;

	operator bool() const {
		return _rc;
	}

	void incr() {
		if(_rc) _rc->_count++;
	}

	void decr() {
		if (_rc) {
			_rc->_count--;
			if (_rc->_count == 0) onCountZero();
		}
	}

	RefCountedPtr() : _rc(NULL) {

	}

	RefCountedPtr(T *val) {
		_rc = new RefCounter(val);
		incr();
	}

	RefCountedPtr(const RefCountedPtr &p) : _rc(p._rc) {
		incr();
	}

	~RefCountedPtr() {
		decr();
	}

	T *operator->() {
		return (T *) (_rc ? _rc->_val : NULL);
	}

	RefCountedPtr &operator=(const RefCountedPtr &p) {
		decr();
		return RefCountedPtr(p);
	}
};

#endif