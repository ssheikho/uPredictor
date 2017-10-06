#ifndef PROCESS_PIPEWORK_H
#define PROCESS_PIPEWORK_H

#include "Allocator.h"
#include "ProcessMultiplexer.h"
#include "ProcessingPipeline.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

template<typename T> class ProcessPipework {
protected:
	//int _poolDepth;
	UBC::Allocator<T> &_alloc;
	ProcessMultiplexer<T> _rootNode;

	map<string, TypeRecipientBroadcaster<T> *> _trb;
	vector<ProcessingPipeline<T> *> _pp;

public:
	ProcessPipework(UBC::Allocator<T> &alloc) :
		_alloc(alloc) {}

	~ProcessPipework() {}

	void addNamedPipelineAtRoot(string name) {
		ProcessingPipeline<T> *pp = new ProcessingPipeline<T>(_alloc);
		_rootNode.addRecipient(pp);
		_trb[name] = pp;
		_pp.push_back(pp);
	}

	void addProcToNamedPipeline(
		string parentName
		, shared_ptr<TypeRecipient<T>> pp) {
		TypeRecipientBroadcaster<T> *parent = _trb[parentName];
		parent->addProc(pp);
	}

	void addRecipientToNamedPipeline(
		string parentName
		, TypeRecipient<T> *pp) {
		TypeRecipientBroadcaster<T> *parent = _trb[parentName];
		parent->addRecipient(pp);
	}

	void addNamedPipelineUnderParent(string parentName, string name) {
		TypeRecipientBroadcaster<T> *parent = _trb[parentName];
		ProcessingPipeline<T> *pp = new ProcessingPipeline<T>(_alloc);
		parent->addRecipient(pp);
		_trb[name] = pp;
		_pp.push_back(pp);
	}

	void addProcessMerger(string name) {
		ProcessMerger<T> *pm = new ProcessMerger<T>();
		_trb[name] = pm;
	}

	void addPipelineToMerger(string merger, string process) {
		TypeRecipientBroadcaster<T> *parent = _trb[merger];
		parent->addProc(shared_ptr<TypeRecipient<T>>(_trb[process]));
	}

	ProcessMultiplexer<T> &getRoot() {
		return _rootNode;
	}

	void start() {
		for (vector<ProcessingPipeline<T> *>::iterator iter =
			_pp.begin();
			iter != _pp.end();
			iter++) {
			(*iter)->start();
		}
	}
};

#endif