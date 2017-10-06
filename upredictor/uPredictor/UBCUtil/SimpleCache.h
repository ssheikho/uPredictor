#ifndef SIMPLE_CACHE_H
#define SIMPLE_CACHE_H

#include "TypeFactory.h"

#include <vector>

template<typename T> class SimpleCache {
public:
	SimpleCache(TypeFactory<T> *tf) : _tf(tf) {}

	~SimpleCache() {
		for (typename std::vector<T *>::iterator iter = _v.begin()
			; iter != _v.end(); iter++) {
			delete *iter;
		}
	}

	T *get(size_t index) {
		while (_v.size() <= index) _v.push_back(_tf->getInstance());
		return _v[index];
	}

protected:
	TypeFactory<T> *_tf;
	std::vector<T *> _v;
};

#endif
