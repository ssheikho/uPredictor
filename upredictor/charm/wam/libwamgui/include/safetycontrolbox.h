#ifndef SAFETY_CONTROL_BOX_H
#define SAFETY_CONTROL_BOX_H

#include "ExternalUpdate.h"
#include "gridwrapper.h"
#include "safetycontrols.h"

class SafetyControlBox : public ExternalUpdate {
	public:
		SafetyControlBox(SafetyControls &sc, bool frame = true);
		~SafetyControlBox();

		GtkWidget *getWidget();
		GridWrapper &getGrid();

		static void setCB(GtkWidget *widget, gpointer data);
		void set();

		void update();
		bool hasFutureUpdates();

	protected:
		SafetyControls &_sc;

		GtkWidget	*_frame,
					*_emptyLabel1,	*_emptyLabel2,
					*_warnLabel,	*_faultLabel,		*_velocityLabel,
					*_velWarnEntry,	*_velFaultEntry,
					*_setButton;

		GridWrapper _gw;
};

#endif
