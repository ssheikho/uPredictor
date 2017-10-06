#ifndef PROCESS_PIPELINE_EXEC_H
#define PROCESS_PIPELINE_EXEC_H

#include "ProcessPipelineCounter.h"

template<typename T> class ProcessPipelineExec :
	public TypeRecipient<ProcessPipelineCounter<T> *> {
protected:
	shared_ptr<TypeRecipient<T>> _proc;

public:
	ProcessPipelineExec(shared_ptr<TypeRecipient<T>> proc) :
		_proc(proc) {}
	~ProcessPipelineExec() {}

	void processType(ProcessPipelineCounter<T> *t) {
		t->runProc(_proc);
	}

	void onStartup() {
		_proc->onStartup();
	}
};

#endif