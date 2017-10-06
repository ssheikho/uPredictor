#include "handcontrolbox.h"
#include "handcontrol.h"

HandControlBox::HandControlBox(HandControl &hc, bool frame) : _hc(hc),
	_frame(NULL) {
	_label = gtk_label_new("Hand");
	_openButton = gtk_button_new_with_label("Open");
	_closeButton = gtk_button_new_with_label("Close");

	_gw.addRow();
	_gw.addChild(_label);
	_gw.addChild(_openButton);
	_gw.addChild(_closeButton);

    g_signal_connect(_openButton, "clicked", G_CALLBACK(openCB),
		(gpointer) this);
    g_signal_connect(_closeButton, "clicked", G_CALLBACK(closeCB),
		(gpointer) this);

	if(frame) {
		_frame = gtk_frame_new("Hand Controls");
		//gtk_frame_set_shadow_type(GTK_FRAME(_frame), GTK_SHADOW_ETCHED_OUT);
		gtk_container_add(GTK_CONTAINER(_frame), _gw.getWidget());
	}
}

HandControlBox::~HandControlBox() {}

GtkWidget *HandControlBox::getWidget() {
	return _frame ? _frame : _gw.getWidget();
}

GridWrapper &HandControlBox::getGrid()	{	return _gw;				}

void HandControlBox::openCB(GtkWidget *widget, gpointer data) {
	((HandControlBox *)data)->_hc.open();
}

void HandControlBox::closeCB(GtkWidget *widget, gpointer data) {
	((HandControlBox *)data)->_hc.close();
}
