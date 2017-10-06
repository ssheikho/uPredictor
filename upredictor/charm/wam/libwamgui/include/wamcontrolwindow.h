#ifndef WAM_CONTROL_WINDOW_H
#define WAM_CONTROL_WINDOW_H

#include "armcontrolbox.h"
#include "armposeinterpreter.h"
#include "cmdstrline.h"
#include "handcontrolbox.h"
#include "posline.h"
#include "poslistcb.h"
#include "posgrid.h"
#include "safetycontrolbox.h"

class ArmPoser;
class HandControl;
class PosList;
class SafetyControls;

class WAMControlWindow {
	public:
		WAMControlWindow(	PosList &pl, ArmPoser &ap, HandControl &hc,
							SafetyControls &sc);
		~WAMControlWindow();

		GtkWidget *getWindow();

	protected:
		PosList &_pl;
		ArmPoser &_ap;
		HandControl &_hc;
		SafetyControls &_sc;

		ArmPoseInterpreter _api;

		PosLine _cpl, _mpl;
		HandControlBox _hcb;
		ArmControlBox _acb;
		SafetyControlBox _scb;
		PosGrid _pg;
		PosListCB _plcb;
		CmdStrLine _csl;

		GtkWidget *_window, *_align, *_vbox;
};

#endif
