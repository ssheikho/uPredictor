#ifndef CMD_STR_LINE_H
#define CMD_STR_LINE_H

#include "ExternalUpdate.h"
#include "gridwrapper.h"
#include "updatebutton.h"

class CmdStringInterpreter;

class CmdStrLine : public ExternalUpdate {
	public:
		CmdStrLine(	CmdStringInterpreter &csi,
					string frameName = "", bool frame = true);
		~CmdStrLine();

		GtkWidget *getWidget();
		GridWrapper &getGrid();

		void update();
		bool hasFutureUpdates();

	protected:
		CmdStringInterpreter &_csi;
		UpdateButton _ub;
		GtkEntry *_entry;
		GtkWidget *_frame;
		GridWrapper _gw;
};

#endif
