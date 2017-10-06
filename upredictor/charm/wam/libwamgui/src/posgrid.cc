#include "posgrid.h"
#include "armpose.h"
#include "armposer.h"
#include "poslist.h"

#include <iostream>

PosGrid::PosGrid(PosList &pl, ArmPoser &armPoser, bool frame) :
	_pl(pl), _armPoser(armPoser), _frame(NULL), _curRow(0), _curCol(0) {
	for(int i = 0; i < _pl.rows(); i++)
		_rows.push_back(new GridLine(*this, _pl.getPos(i)));

	_scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

	gtk_container_add(GTK_CONTAINER(_scrolledWindow),
		GTK_WIDGET(_posGrid.getWidget()));

    GtkWidget* viewport =
		gtk_widget_get_ancestor(_posGrid.getWidget(), GTK_TYPE_VIEWPORT);
	GtkRequisition sizeA, sizeB;
    gtk_widget_get_preferred_size(viewport, &sizeA, &sizeB);
    gtk_widget_set_size_request(_scrolledWindow, 1600, 500);

	if(frame) {
		_frame = gtk_frame_new("Arm Positions");
		//gtk_frame_set_shadow_type(GTK_FRAME(_frame), GTK_SHADOW_ETCHED_OUT);
		gtk_container_add(GTK_CONTAINER(_frame), _scrolledWindow);
	}
}

PosGrid::~PosGrid() {}

GtkWidget *PosGrid::getWidget()	{
	return _frame ? _frame : _scrolledWindow;
}

GridWrapper &PosGrid::getGrid()	{	return _posGrid;				}

PosGrid::GridLine::GridLine(PosGrid &pg, ArmPose *ap) : _pg(pg), _ap(ap) {
	init();
	refreshText();
}

void PosGrid::GridLine::init() {
	GtkWidget *w = gtk_entry_new();
	
	_pg._posGrid.addRow();
	_pg._posGrid.addChild(w);
	_entries.push_back((GtkEntry *)w);
	
	for(int i = 0; i < _pg._pl.getDOF(); i++) {
		GtkWidget *w = gtk_entry_new();
		_pg._posGrid.addChild(w);
		_entries.push_back((GtkEntry *)w);
	}

	_setButton = gtk_button_new_with_label("Set");
	_delButton = gtk_button_new_with_label("Delete");
	_copyButton = gtk_button_new_with_label("Copy Current");
	_moveButton = gtk_button_new_with_label("Move");
	
	_pg._posGrid.addChild(_setButton);
	_pg._posGrid.addChild(_delButton);
	_pg._posGrid.addChild(_copyButton);
	_pg._posGrid.addChild(_moveButton);

    g_signal_connect (_setButton, "clicked", G_CALLBACK(setCB),
		(gpointer) this);
    g_signal_connect (_delButton, "clicked", G_CALLBACK(delCB),
		(gpointer) this);
    g_signal_connect (_copyButton, "clicked", G_CALLBACK(copyCB),
		(gpointer) this);
    g_signal_connect (_moveButton, "clicked", G_CALLBACK(moveCB),
		(gpointer) this);

	_pg._posGrid.addRow();
}

ArmPose *PosGrid::GridLine::getArmPose() {
	return _ap;
}

void PosGrid::GridLine::refreshText() {
	if(_ap) {
		gtk_entry_set_text(_entries[0], _ap->getName().c_str());
		//cout << "_ap->getNAngs():	" << _ap->getNAngs() << endl;
		for(int i = 0; i < _ap->getNAngs(); i++) {
	   		ostringstream ss;
			ss << _ap->getAng(i);
			gtk_entry_set_text(_entries[i + 1], ss.str().c_str());
			ss.clear();
		}
	}
}

void PosGrid::GridLine::setLine() {
	for(int i = 0; i < _ap->getNAngs(); i++) {
		cout << "A" << i << ":	" << gtk_entry_get_text(_entries[i + 1]) <<
			endl;
	}
}

void PosGrid::GridLine::setCB(GtkWidget *widget, gpointer data) {
	((PosGrid::GridLine *)data)->setLine();
}

void PosGrid::GridLine::delCB(GtkWidget *widget, gpointer data) {
	cout << "NOT SUPPORTED" << endl;
}

void PosGrid::GridLine::copyCB(GtkWidget *widget, gpointer data) {
	PosGrid::GridLine *gl = (PosGrid::GridLine *)data;
	gl->_pg._armPoser.copyInto(*gl->_ap);
	gl->refreshText();
}

void PosGrid::GridLine::moveCB(GtkWidget *widget, gpointer data) {
	PosGrid::GridLine *gl = (PosGrid::GridLine *)data;
	ArmPoser &ap = gl->_pg._armPoser;
	ap.updatePose(gl->_ap);
}

PosGrid::GridLine::~GridLine() {
	
}
