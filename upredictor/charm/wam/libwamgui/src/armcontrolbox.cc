#include "armcontrolbox.h"
#include "armposer.h"

ArmControlBox::ArmControlBox(ArmPoser &armPoser, bool frame) :
	_armPoser(armPoser), _frame(NULL) {
	_label = gtk_label_new("Arm");
	_idleButton = gtk_button_new_with_label("Idle");

	_gw.addRow();
	_gw.addChild(_label);
	_gw.addChild(_idleButton);

    g_signal_connect(_idleButton, "clicked", G_CALLBACK(idleCB),
		(gpointer) this);

	if(frame) {
		_frame = gtk_frame_new("Arm Controls");
		//gtk_frame_set_shadow_type(GTK_FRAME(_frame), GTK_SHADOW_ETCHED_OUT);
		gtk_container_add(GTK_CONTAINER(_frame), _gw.getWidget());
	}
}

ArmControlBox::~ArmControlBox() {}

GtkWidget *ArmControlBox::getWidget() {
	return _frame ? _frame : _gw.getWidget();
}

GridWrapper &ArmControlBox::getGrid()	{	return _gw;				}
void ArmControlBox::idle()				{	_armPoser.idle();		}

void ArmControlBox::idleCB(GtkWidget *widget, gpointer data) {
	((ArmControlBox *)data)->idle();
}
