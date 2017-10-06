#ifndef AUTO_RESIZE_WINDOW_H
#define AUTO_RESIZE_WINDOW_H

#include "LayoutContainer.h"
#include "DefaultShutdownInterface.h"

#include <map>

using namespace std;

class AutoResizeWindow : public LayoutContainer
	, public DefaultShutdownInterface {
public:
	AutoResizeWindow(int minW, int minH);
	~AutoResizeWindow();

	void addChild(LayoutElement *child);
	GtkWidget *getWidget();

	static void *delete_event(GtkWidget *widget, void *data);

protected:
	void onStartup();
	void onShutdown();
	void onAddChained(ShutdownInterface *si);

	GtkWidget *_widget;
};

#endif
