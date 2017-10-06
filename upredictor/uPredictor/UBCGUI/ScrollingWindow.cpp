#include "ScrollingWindow.h"

ScrollingWindow::ScrollingWindow(LayoutContainer *parent, int w, int h) :
	_parent(parent)
	{
	_widget = gtk_scrolled_window_new(NULL, NULL);
	_parent->addChild(this);

	// Scrolled window only holds one widget, so create an inner box
	// to allow multiple widgets
	_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add(GTK_CONTAINER(_widget), _box);
}

ScrollingWindow::~ScrollingWindow() {
	gtk_widget_destroy(_widget);
}

GtkWidget *ScrollingWindow::getWidget() {
	return _widget;
}

void ScrollingWindow::addChild(LayoutElement *child) {
	gtk_container_add(GTK_CONTAINER(_box), child->getWidget());
}

