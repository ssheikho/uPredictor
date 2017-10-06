#ifndef GTK_SHUTDOWN_INTERFACE_H
#define GTK_SHUTDOWN_INTERFACE_H

#include "DefaultShutdownInterface.h"

class GTKShutdownInterface : public DefaultShutdownInterface {
public:
	GTKShutdownInterface();
	~GTKShutdownInterface();

protected:
	void onStartup();
	void onShutdown();
	void onAddChained(ShutdownInterface *si);
};

#endif
