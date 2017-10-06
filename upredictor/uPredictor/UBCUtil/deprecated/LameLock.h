#ifndef LAME_LOCK_H
#define LAME_LOCK_H

#define NOMINMAX
#include <WinSock2.h>
#include <Windows.h>

#include <stack>
#include <string>

using namespace std;

class LameLock {
public:
	LameLock();
	~LameLock();

	void lock(string s);
	void unlock();

protected:
	HANDLE _mutex;
	stack<string> _locks;
};

#endif