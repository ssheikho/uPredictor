#ifndef TYPE_BROADCASTER_H
#define TYPE_BROADCASTER_H

#include "TypeRecipient.h"

#include <memory>
#include <vector>

using namespace std;

template <typename T> class TypeBroadcaster {
protected:

	typedef typename vector<TypeRecipient<T> *>::iterator TypeRecipientVectorIterator;

	vector<TypeRecipient<T> *> _or;

	void fireUpdate(T t) {
		for (
			TypeRecipientVectorIterator iter = _or.begin();
			iter != _or.end(); iter++)
			(*iter)->processType(t);
	}

	/*
	void onStartup() {
		for (
			vector<TypeRecipient<T> *>::iterator iter = _or.begin();
			iter != _or.end(); iter++)
			(*iter)->onStartup();
	}
	*/

public:
	void addRecipient(TypeRecipient<T> *tr) {
		_or.push_back(tr);
	}
};

#endif
