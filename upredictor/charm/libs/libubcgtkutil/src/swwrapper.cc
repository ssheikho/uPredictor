#include "swwrapper.h"

SWWrapper::SWWrapper() {
	_scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
}

SWWrapper::~SWWrapper() {}

void SWWrapper::update() {}

void SWWrapper::setChild(GtkWidget *child) {
	gtk_container_add(
		GTK_CONTAINER(_scrolledWindow), GTK_WIDGET(_child = child));
	requestFullChildWidth();
}

GtkWidget *SWWrapper::getWidget() {}

void SWWrapper::requestFullChildWidth() {
    GtkWidget* viewport = gtk_widget_get_ancestor(_child, GTK_TYPE_VIEWPORT);

	GtkRequisition sizeA, sizeB;
    gtk_widget_get_preferred_size(viewport, &sizeA, &sizeB);
    gtk_widget_set_size_request(_scrolledWindow, 1500, 500);
}
