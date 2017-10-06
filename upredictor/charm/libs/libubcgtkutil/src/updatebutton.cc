#include "updatebutton.h"

UpdateButton::UpdateButton(ExternalUpdate &eu, string label) : _eu(eu) {
	_button = gtk_button_new_with_label(label.c_str());
}

UpdateButton::~UpdateButton() {}

void UpdateButton::update() { _eu.update();	}

bool UpdateButton::hasFutureUpdates() { return true;	}

void UpdateButton::updateCB(GtkWidget *widget, gpointer data) {
	((UpdateButton *)data)->update();
}

GtkWidget *UpdateButton::getWidget() {	return _button;	}
