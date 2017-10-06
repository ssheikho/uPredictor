#ifndef UPDATE_BUTTON_H
#define UPDATE_BUTTON_H

#include "ExternalUpdate.h"
#include <gtk/gtk.h>

#include <string>

using namespace std;

class UpdateButton : public ExternalUpdate {
	public:
		UpdateButton(ExternalUpdate &eu, string label);
		~UpdateButton();

		void update();
		bool hasFutureUpdates();
		static void updateCB(GtkWidget *widget, gpointer data);

		GtkWidget *getWidget();

	protected:
		ExternalUpdate &_eu;
		GtkWidget *_button;
};

#endif
