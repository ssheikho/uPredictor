#ifndef PROCESS_MERGER_H
#define PROCESS_MERGER_H

#include <Allocator.h>
#include <SimplePool.h>
#include <TypeRecipientBroadcaster.h>

#include <map>
#include <memory>
#include <set>

using namespace std;

template<typename T> class ProcessMerger :
	public TypeRecipientBroadcaster<T> {
protected:
	int _nBranches;

	map<T, int> _counters;

public:
	void processType(T t) {
		map<T, int>::iterator iter = _counters.find(t);
		if (iter == _counters.end()) {
			_counters[t] = 1;
		}
		else {
			_counters[t] = _counters[t] + 1;
 		}

		if (_counters[t] == _nBranches) {
			_counters[t] = 0;
			fireUpdate(t);
		}
	}

	void addProc(shared_ptr<TypeRecipient> proc) {
		this->addRecipient(proc.get());
	}

};

#endif