#include "GTKShutdownInterface.h"

#include <cstdlib>
#include <iostream>

using namespace std;

GTKShutdownInterface::GTKShutdownInterface() {}

GTKShutdownInterface::~GTKShutdownInterface() {}

void GTKShutdownInterface::onStartup() {}

void GTKShutdownInterface::onShutdown() {
	//cout << "A!" << endl;
	exit(0);
}

void GTKShutdownInterface::onAddChained(ShutdownInterface *si) {
	//cout << "C!" << endl;
}
