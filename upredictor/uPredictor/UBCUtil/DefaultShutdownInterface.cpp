#include "DefaultShutdownInterface.h"
//#include <iostream>

//using namespace std;

DefaultShutdownInterface::DefaultShutdownInterface() : _isRunning(false) {}
DefaultShutdownInterface::~DefaultShutdownInterface() {}

bool DefaultShutdownInterface::isRunning() {
	return _isRunning;
}

void DefaultShutdownInterface::doStartup() {
	_isRunning = true;
}

void DefaultShutdownInterface::doShutdown() {
	//cout << "DefaultShutdownInterface::doShutdown()" << endl;
	_isRunning = false;
}
