#ifndef SHUTDOWN_INTERFACE_H
#define SHUTDOWN_INTERFACE_H

#include <vector>

using namespace std;

class ShutdownInterface {
public:
	ShutdownInterface();
	~ShutdownInterface();

	void startup();
	void shutdown();
	virtual bool isRunning() = 0;

	void addChainedSI(ShutdownInterface *si);

protected:
	void fireChainedShutdown();

	virtual void doStartup() = 0;
	virtual void doShutdown() = 0;

	virtual void onStartup() = 0;
	virtual void onShutdown() = 0;
	virtual void onAddChained(ShutdownInterface *si) = 0;

	vector<ShutdownInterface *> _si;
};

#endif