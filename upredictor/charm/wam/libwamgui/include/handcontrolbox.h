#ifndef HAND_CONTROL_BOX_H
#define HAND_CONTROL_BOX_H

#include "gridwrapper.h"

class HandControl;

class HandControlBox {
	public:
		HandControlBox(HandControl &hc, bool frame = true);
		~HandControlBox();

		GtkWidget *getWidget();
		GridWrapper &getGrid();

		static void openCB(GtkWidget *widget, gpointer data);
		static void closeCB(GtkWidget *widget, gpointer data);

	protected:
		HandControl &_hc;
		GridWrapper _gw;
		GtkWidget *_frame, *_label, *_openButton, *_closeButton;
};

#endif
