#include "safetycontrolbox.h"

#include <cstdlib>

using namespace std;

SafetyControlBox::SafetyControlBox(SafetyControls &sc, bool frame) :
	_sc(sc), _frame(NULL) {
	_emptyLabel1 = gtk_label_new("");
	_emptyLabel2 = gtk_label_new("");

	_warnLabel = gtk_label_new("Warning");
	_faultLabel = gtk_label_new("Fault");
	_velocityLabel = gtk_label_new("Velocity");

	_velWarnEntry = gtk_entry_new();
	_velFaultEntry = gtk_entry_new();

	_setButton = gtk_button_new_with_label("Set");

	_gw.addRow();
	//_gw.skipChild();
	_gw.addChild(_emptyLabel1);
	_gw.addChild(_warnLabel);
	_gw.addChild(_faultLabel);

	_gw.addRow();
	_gw.addChild(_velocityLabel);
	_gw.addChild(_velWarnEntry);
	_gw.addChild(_velFaultEntry);

	_gw.addRow();
	_gw.addChild(_emptyLabel2);
	_gw.addChild(_setButton);

    g_signal_connect (_setButton, "clicked", G_CALLBACK(setCB),
		(gpointer) this);

	if(frame) {
		_frame = gtk_frame_new("WAM Pendant Safety Limits");
		//gtk_frame_set_shadow_type(GTK_FRAME(_frame), GTK_SHADOW_ETCHED_OUT);
		gtk_container_add(GTK_CONTAINER(_frame), _gw.getWidget());
	}
}

SafetyControlBox::~SafetyControlBox() {}

GtkWidget *SafetyControlBox::getWidget() {
	return _frame ? _frame : _gw.getWidget();
}

GridWrapper &SafetyControlBox::getGrid() {	return _gw;				}

void SafetyControlBox::setCB(GtkWidget *widget, gpointer data) {
	((SafetyControlBox *)data)->set();
}

void SafetyControlBox::set() {
	_sc.setVelocityLimit(
		atof(gtk_entry_get_text(GTK_ENTRY(_velWarnEntry))),
		atof(gtk_entry_get_text(GTK_ENTRY(_velFaultEntry))));
}

void SafetyControlBox::update() {
	gtk_entry_set_text(
		GTK_ENTRY(_velWarnEntry),
		_sc.getVelocityWarnLimitString().c_str());
	gtk_entry_set_text(
		GTK_ENTRY(_velFaultEntry),
		_sc.getVelocityFaultLimitString().c_str());
}

bool SafetyControlBox::hasFutureUpdates() {
	return true;
}
