#include "poslistcb.h"
#include "poslist.h"

#include <iostream>

PosListCB::PosListCB(PosList &pl, string filename, bool frame) :
	_pl(pl), _frame(NULL) {
	_filenameEntry = (GtkEntry *)gtk_entry_new();
	gtk_entry_set_text(_filenameEntry, filename.c_str());

	_gw.addRow();
	_loadButton = gtk_button_new_with_label("Load");
	_saveButton = gtk_button_new_with_label("Save");
	_addLineButton = gtk_button_new_with_label("Add Line");
	
	_gw.addChild((GtkWidget *)_filenameEntry, 4);
	_gw.addChild(_loadButton);
	_gw.addChild(_saveButton);
	_gw.addChild(_addLineButton);

    g_signal_connect (_loadButton, "clicked", G_CALLBACK(loadCB),
		(gpointer) this);
    g_signal_connect (_saveButton, "clicked", G_CALLBACK(saveCB),
		(gpointer) this);
    g_signal_connect (_addLineButton, "clicked", G_CALLBACK(addLineCB),
		(gpointer) this);

	if(frame) {
		_frame = gtk_frame_new("Arm Position File");
		//gtk_frame_set_shadow_type(GTK_FRAME(_frame), GTK_SHADOW_ETCHED_OUT);
		gtk_container_add(GTK_CONTAINER(_frame), _gw.getWidget());
	}
}

PosListCB::~PosListCB() {}

void PosListCB::load()		{	cout << "NOT SUPPORTED" << endl; 			}
void PosListCB::addLine()	{	cout << "NOT SUPPORTED"  << endl;			}
void PosListCB::save() {	_pl.save(gtk_entry_get_text(_filenameEntry));	}

GtkWidget *PosListCB::getWidget() {
	return _frame ? _frame : _gw.getWidget();
}

GridWrapper &PosListCB::getGrid() {	return _gw;				}

void PosListCB::loadCB(GtkWidget *widget, gpointer data) {
	((PosListCB *)data)->load();
}

void PosListCB::saveCB(GtkWidget *widget, gpointer data) {
	((PosListCB *)data)->save();
}

void PosListCB::addLineCB(GtkWidget *widget, gpointer data) {
	((PosListCB *)data)->addLine();
}
