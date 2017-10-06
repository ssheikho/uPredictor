#include "ExternalUpdateThread.h"

#ifdef _WIN32
static DWORD WINAPI eutThread(LPVOID lpParam) {
#elif __linux__
void *eutThread(void *lpParam) {
#endif
	ExternalUpdateThread *eut = (ExternalUpdateThread *)lpParam;
	eut->onStartup();
	while (eut->hasFutureUpdates()) eut->update();
	return NULL;
}

ExternalUpdateThread::ExternalUpdateThread(ExternalUpdate &eu) : _eu(eu),
_started(false) {}

ExternalUpdateThread::~ExternalUpdateThread() {
	stop();
}

void ExternalUpdateThread::start() {
	if (!_started) {
		_started = true;
		#ifdef _WIN32
			_thread = CreateThread(NULL, 0, eutThread, this, 0, NULL);
		#elif __linux__
			pthread_create(&_thread, NULL, eutThread, this);
		#endif
	}
}

void ExternalUpdateThread::stop() {
	if (_started) {
		_started = false;
		#ifdef _WIN32
			WaitForSingleObject(_thread, INFINITE);
		#elif __linux__
			pthread_join(_thread, NULL);
		#endif
	}
}

void ExternalUpdateThread::update() {
	_eu.update();
}

bool ExternalUpdateThread::hasFutureUpdates() {
	bool hfu = _eu.hasFutureUpdates();
	return _started && hfu;
}

void ExternalUpdateThread::onStartup() {
	_eu.onStartup();
}
