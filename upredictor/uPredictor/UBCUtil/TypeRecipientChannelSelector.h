#ifndef TYPE_RECIP_CHANNEL_SELECTOR_H
#define TYPE_RECIP_CHANNEL_SELECTOR_H

#include "IntSwitch.h"
#include "TypeRecipient.h"

#include <vector>

using namespace std;

template <typename T> class TypeRecipientChannelSelector :
	public TypeRecipient <T>
	, public IntSwitch
{
public:
	TypeRecipientChannelSelector() : _curChan(0) {}

	void add(TypeRecipient <T> *tr) {
		_tr.push_back(tr);
	}

	void processType(T t) {
		_tr[_curChan]->processType(t);
	}

	void onStartup() {}

	void updateSwitch(int val) {
		_curChan = val;
	}

protected:
	int _curChan;
	vector<TypeRecipient <T> *> _tr;
};

#endif