#include "ShutdownContainer.h"
#include <iostream>

using namespace std;

ShutdownContainer::ShutdownContainer() {
	startup();
}

ShutdownContainer::~ShutdownContainer() {}

void ShutdownContainer::onStartup() {
	for(int i = 0; i < _si.size(); i++)
		if(!_si[i]->isRunning())	_si[i]->startup();
}

void ShutdownContainer::onShutdown() {
	for(int i = 0; i < _si.size(); i++)
		if(_si[i]->isRunning())	_si[i]->shutdown();
}

void ShutdownContainer::onAddChained(ShutdownInterface *si) {
	//cout << "B!" << endl;
	si->addChainedSI(this);
}
