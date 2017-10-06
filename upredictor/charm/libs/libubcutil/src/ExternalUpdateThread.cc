#include "ExternalUpdateThread.h"

static DWORD WINAPI eutThread(LPVOID lpParam) {
	ExternalUpdateThread *eut = (ExternalUpdateThread *)lpParam;
	while (eut->hasFutureUpdates()) eut->update();
	return NULL;
}

ExternalUpdateThread::ExternalUpdateThread(ExternalUpdate &eu) : _eu(eu),
_started(false) {}

ExternalUpdateThread::~ExternalUpdateThread() {
	WaitForSingleObject(_thread, INFINITE);
}

void ExternalUpdateThread::start() {
	if (!_started) {
		_started = true;
		_thread = CreateThread(NULL, 0, eutThread, this, 0, NULL);
	}
}

void ExternalUpdateThread::stop() {
	if (_started) {
		_started = false;
		WaitForSingleObject(_thread, INFINITE);
	}
}

void ExternalUpdateThread::update() {
	_eu.update();
}

bool ExternalUpdateThread::hasFutureUpdates() {
	return _started && _eu.hasFutureUpdates();
}