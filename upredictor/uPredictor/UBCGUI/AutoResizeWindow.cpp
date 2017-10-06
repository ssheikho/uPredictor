#include "AutoResizeWindow.h"
#include <iostream>

using namespace std;

void *AutoResizeWindow::delete_event(GtkWidget *widget, void *data) {
	//cout << data << endl;
	((AutoResizeWindow*)data)->shutdown();
	return NULL;
}

AutoResizeWindow::AutoResizeWindow(int minW, int minH) {
	_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(_widget), true);
	gtk_widget_set_size_request(_widget,minW,minH);
	g_signal_connect (G_OBJECT(_widget), "destroy"
		, G_CALLBACK(delete_event), (gpointer)this);
	//cout << this << endl;
}

AutoResizeWindow::~AutoResizeWindow() {
	gtk_widget_destroy(_widget);
}

void AutoResizeWindow::onStartup() {}

void AutoResizeWindow::onShutdown() {
	//cout << "OMG" << endl;
	gtk_widget_destroy(_widget);
}

void AutoResizeWindow::onAddChained(ShutdownInterface *si) {}

void AutoResizeWindow::addChild(LayoutElement *child) {
	gtk_container_add(GTK_CONTAINER(_widget), child->getWidget());
}

GtkWidget *AutoResizeWindow::getWidget() {
	return _widget;
}
