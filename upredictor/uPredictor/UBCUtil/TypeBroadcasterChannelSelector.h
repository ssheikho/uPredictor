#ifndef TYPE_BROADCASTER_CHANNEL_SELECTOR_H
#define TYPE_BROADCASTER_CHANNEL_SELECTOR_H

#include "IntSwitch.h"
#include "TypeBroadcaster.h"

#include <map>

using namespace std;

template <typename T> class TypeBroadcasterChannelSelector :
	public TypeBroadcaster<T>
	, public IntSwitch
{
public:
	TypeBroadcasterChannelSelector() : _curChan(0) {}

	void addChannel(TypeBroadcaster<T> *tb) {
		_chans.push_back(new Channel(this, tb, _chans.size()));
	}

	void updateSwitch(int val) {
		_curChan._t = val;
	}

	ValueListener<long> _curChan;

protected:
	class Channel : public TypeRecipient <T> {
	public:
		Channel(
			TypeBroadcasterChannelSelector *tbcs
			, TypeBroadcaster<T> *tb
			, int chanNo) : _tbcs(tbcs), _chanNo(chanNo) {
			tb->addRecipient(this);
		}

		~Channel() {}

		void processType(T t) {
			if (_tbcs->_curChan._t == _chanNo) {
				_tbcs->fireUpdate(t);
			}
		}

		void onStartup() {}

	protected:
		TypeBroadcasterChannelSelector *_tbcs;
		int _chanNo;
	};

	vector<Channel *> _chans;
};

#endif