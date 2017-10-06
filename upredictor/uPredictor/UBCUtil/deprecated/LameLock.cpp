#include "LameLock.h"

LameLock::LameLock() {
	_mutex = CreateMutex(NULL, FALSE, NULL);
}

LameLock::~LameLock() {
	CloseHandle(_mutex);
}

void LameLock::lock(string lockHolder) {
	WaitForSingleObject(_mutex, INFINITE);
	_locks.push(lockHolder);
}

void LameLock::unlock() {
	_locks.pop();
	ReleaseMutex(_mutex);
}