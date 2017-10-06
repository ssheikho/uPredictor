#include "wamcontrolwindow.h"
#include "poslist.h"

WAMControlWindow::WAMControlWindow(
	PosList &pl, ArmPoser &ap, HandControl &hc, SafetyControls &sc) :
	_pl(pl), _ap(ap), _hc(hc), _sc(sc),
	_api(_ap, _pl), 
	_cpl(_pl, _ap, true),								//Current PosLine 
	_mpl(_pl, _ap, false, true, "Recorded Arm Pose"),	//Move PosLine
	_hcb(_hc), _acb(_ap), _scb(_sc), _pg(_pl, _ap),
	_plcb(_pl,
		"../../ROS/catkin_ws/src/timing/wam/src/joint_coordinates.txt"),
	_csl(_api, "Arm Command Line", true) {
	_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	_align = gtk_alignment_new (0.5, 0.5, 1, 1);
	_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_container_add(GTK_CONTAINER(_window), GTK_WIDGET(_align));
	gtk_container_add(GTK_CONTAINER(_align), GTK_WIDGET(_vbox));

	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_scb.getWidget()));
	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_hcb.getWidget()));
	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_acb.getWidget()));
	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_cpl.getWidget()));
	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_mpl.getWidget()));
	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_pg.getWidget()));
	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_csl.getWidget()));
	gtk_container_add(GTK_CONTAINER(_vbox), GTK_WIDGET(_plcb.getWidget()));

	g_signal_connect_swapped(_window, "destroy", G_CALLBACK (gtk_main_quit),
		NULL);

	_cpl.getGrid().addAlignRequest(&_pg.getGrid());
	_mpl.getGrid().addAlignRequest(&_pg.getGrid());
	_hcb.getGrid().addAlignRequest(&_pg.getGrid());
	_acb.getGrid().addAlignRequest(&_pg.getGrid());
	_scb.getGrid().addAlignRequest(&_pg.getGrid());
	_plcb.getGrid().addAlignRequest(&_pg.getGrid());
	_csl.getGrid().addAlignRequest(&_pg.getGrid());
}

WAMControlWindow::~WAMControlWindow() {}

GtkWidget *WAMControlWindow::getWindow() {
	return _window;
}
