#include "cmdstrline.h"

CmdStrLine::CmdStrLine(CmdStringInterpreter &csi,string frameName, bool frame) :
	_csi(csi), _ub(*this, "→"), _frame(NULL) {
	_entry = GTK_ENTRY(gtk_entry_new());

	_gw.addRow();
	_gw.addChild(GTK_WIDGET(_entry));
	_gw.addChild(_ub.getWidget());
	
	if(frame) {
		_frame = gtk_frame_new(frameName.c_str());
		gtk_container_add(GTK_CONTAINER(_frame), _gw.getWidget());
	}
}

CmdStrLine::~CmdStrLine() {}

GtkWidget *CmdStrLine::getWidget() {
	return _frame ? _frame : _gw.getWidget();
}

GridWrapper &CmdStrLine::getGrid()	{	return _gw;		}

void CmdStrLine::update() {
	
}

bool CmdStrLine::hasFutureUpdates() {
	return true;
}
