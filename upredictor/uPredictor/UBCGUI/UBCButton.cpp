#include "UBCButton.h"
//#include "IntegerIndicator.h"
#include "IndexedToggle.h"
#include "IntSwitch.h"
#include "LayoutContainer.h"
#include "UBCUtil.h"

#include <cstdlib>

void *UBCButton::click_event(GtkWidget *widget, void *data) {
	//cout << data << endl;
	((UBCButton*)data)->updateAppropriately();
	return NULL;
}

UBCButton::UBCButton(
	string text, LayoutContainer *parent
	, IntSwitch *is, int actionIndex
	, int w, int h) :
	_parent(parent)
	, _is(is)
	, _it(NULL)
	, _isChecked(false)
	, _actionIndex(actionIndex)
	, _w(w)
	, _h(h) {
	initialize(text, false);
}

UBCButton::UBCButton(
	string text, LayoutContainer *parent
	, IndexedToggle *it, int actionIndex
	, int w, int h) :
	_parent(parent)
	, _is(NULL)
	, _it(it)
	, _isChecked(false)
	, _actionIndex(actionIndex)
	, _w(w)
	, _h(h) {
	initialize(text, true);
}

void UBCButton::initialize(string text, bool checkbox) {
	if(checkbox) abort();
	_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(_button), text.c_str());
	g_signal_connect (G_OBJECT(_button), "clicked"
		, G_CALLBACK(click_event), (gpointer)this);
	_parent->addChild(this);
}

UBCButton::~UBCButton() {
	gtk_widget_destroy(_button);
}

GtkWidget *UBCButton::getWidget() {
	return _button;
}

void UBCButton::setTextD(double d, int precision) {
	gtk_button_set_label(GTK_BUTTON(_button)
		, doubleToString(d, precision).c_str());
}

void UBCButton::setTextI(long i) {
	gtk_button_set_label(GTK_BUTTON(_button)
		, intToString(i).c_str());
}

void UBCButton::updateAppropriately() {
	if (_is) {
		_is->updateSwitch(_actionIndex);
	}
	else {
		//_isChecked = !_isChecked;
		//SendMessage(_hwndB, BM_SETCHECK
		//	, _isChecked ? BST_CHECKED : BST_UNCHECKED, 0);
		//_it->updateToggle(_actionIndex, _isChecked);
	}
}
