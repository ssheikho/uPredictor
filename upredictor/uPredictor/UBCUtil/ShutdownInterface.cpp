#include "ShutdownInterface.h"

ShutdownInterface::ShutdownInterface() {
	//startup();
}

ShutdownInterface::~ShutdownInterface() {}

void ShutdownInterface::startup() {
	doStartup();
	onStartup();
}

void ShutdownInterface::shutdown() {
	doShutdown();
	onShutdown();
	fireChainedShutdown();
}

void ShutdownInterface::addChainedSI(ShutdownInterface *si) {
	_si.push_back(si);
	onAddChained(si);
}

void ShutdownInterface::fireChainedShutdown() {
	for (vector<ShutdownInterface *>::iterator iter = _si.begin();
	iter != _si.end(); iter++) {
		ShutdownInterface *si = *iter;
		if (si->isRunning()) si->shutdown();
	}
}
