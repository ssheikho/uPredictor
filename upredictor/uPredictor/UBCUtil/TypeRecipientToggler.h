#ifndef TYPE_RECIPIENT_TOGGLER_H
#define TYPE_RECIPIENT_TOGGLER_H

#include "TypeRecipient.h"
#include <vector>

using namespace std;

template<typename T> class TypeRecipientToggler : public TypeRecipient<T> {
public:
	TypeRecipientToggler() : _c(this), _cur(-1) {}
	~TypeRecipientToggler() {}

	void processType(T t) {
		if(_cur >= 0) _r[_cur]->processType(t);
	}

	void onStartup() {}

	void addRecipient(TypeRecipient<T> *r) {
		_r.push_back(r);
	}

	class Controller : public TypeRecipient<long>  {
	public:
		Controller(TypeRecipientToggler *tog) : _tog(tog) {}
		~Controller() {}

		void processType(long t) {
			_tog->_cur = t;
		}

		void onStartup() {}

	protected:
		TypeRecipientToggler *_tog;
	};

	Controller &getC() { return _c;	}

protected:
	Controller _c;
	vector<TypeRecipient<T> *> _r;
	int _cur;
};


#endif
