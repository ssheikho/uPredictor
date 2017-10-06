#include "posline.h"
#include "gridwrapper.h"
//#include "posgrid.h"
#include "poslist.h"

#include <cstdlib>
#include <iostream>

PosLine::PosLine(PosList &pl, ArmPoser &ap, bool listen, bool frame,
	string border) : _ap(ap), _frame(NULL) {

	_posGrid.addRow();

	_label = listen ? gtk_label_new("Current Pose") : gtk_label_new("Pose");
	_posGrid.addChild(_label);


	for(int i = 0; i < pl.getDOF(); i++) {
		GtkWidget *w = gtk_entry_new();
		_posGrid.addChild(w);
		_entries.push_back((GtkEntry *)w);
	}

	if(listen) {
		ap.addListener(this);
	} else {
		_updateButton = gtk_button_new_with_label("Update");
		_moveButton = gtk_button_new_with_label("Move");

		g_signal_connect (_updateButton, "clicked", G_CALLBACK(updateCB),
			(gpointer) this);
		g_signal_connect (_moveButton, "clicked", G_CALLBACK(moveCB),
			(gpointer) this);

		_posGrid.addChild(_updateButton);
		_posGrid.addChild(_moveButton);
	}

	if(frame) {
		_frame = gtk_frame_new(border.c_str());
		//gtk_frame_set_shadow_type(GTK_FRAME(_frame), GTK_SHADOW_ETCHED_OUT);
		gtk_container_add(GTK_CONTAINER(_frame), _posGrid.getWidget());
	}
}

PosLine::~PosLine() {}

GtkWidget *PosLine::getWidget() {
	return _frame ? _frame : _posGrid.getWidget();
}

GridWrapper &PosLine::getGrid() {	return _posGrid;				}

void PosLine::updatePose(ArmPose *pose) {
	for(int i = 0; i < pose->getNAngs(); i++) {
		gtk_entry_set_text(GTK_ENTRY(_entries[i]),
			pose->getAngString(i).c_str());
	}
	
}

void PosLine::updateCB(GtkWidget *widget, gpointer data) {
	PosLine *pl = (PosLine *)data;
	pl->updatePose(&pl->_ap);
}

void PosLine::moveCB(GtkWidget *widget, gpointer data) {
	PosLine *pl = (PosLine *)data;
	pl->_ap.updatePose(pl);
}

string PosLine::getName()					{	return "PosLine";			}
void PosLine::setName(string name)			{	abort();					}
int PosLine::getNAngs()						{	return _entries.size();		}

float PosLine::getAng(int joint) {
	return atof(gtk_entry_get_text(GTK_ENTRY(_entries[joint])));
}

void PosLine::setAng(int joint, float val) {
	ostringstream ss;
	ss << getAng(joint);
	gtk_entry_set_text(GTK_ENTRY(_entries[joint]), ss.str().c_str());
}

