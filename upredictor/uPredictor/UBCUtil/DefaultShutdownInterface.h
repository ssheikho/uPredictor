#ifndef DEFAULT_SHUTDOWN_INTERFACE_H
#define DEFAULT_SHUTDOWN_INTERFACE_H

#include "ShutdownInterface.h"

class DefaultShutdownInterface : public ShutdownInterface {
public:
	DefaultShutdownInterface();
	~DefaultShutdownInterface();

	bool isRunning();

protected:
	virtual void doStartup();
	virtual void doShutdown();

	bool _isRunning;
};

#endif
