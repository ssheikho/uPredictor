#ifndef SHUTDOWN_CONTAINER_H
#define SHUTDOWN_CONTAINER_H

#include "DefaultShutdownInterface.h"

class ShutdownContainer : public DefaultShutdownInterface {
public:
	ShutdownContainer();
	~ShutdownContainer();

protected:
	//ShutdownInterface
	void onStartup();
	void onShutdown();
	void onAddChained(ShutdownInterface *si);
};

#endif
