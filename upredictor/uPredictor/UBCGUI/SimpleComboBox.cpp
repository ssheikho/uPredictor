#include "SimpleComboBox.h"
#include "LayoutContainer.h"

#include <iostream>

void SimpleComboBox::valueChanged(
	GtkComboBox *cb, gpointer user_data) {
	gint val = gtk_combo_box_get_active (cb);
	((SimpleComboBox *)user_data)->fireUpdate(val);
}

SimpleComboBox::SimpleComboBox(
	LayoutContainer *parent) : _parent(parent) {
	_comboBox = gtk_combo_box_text_new();

	g_signal_connect(_comboBox, "changed", G_CALLBACK(valueChanged)
		, (gpointer)this);


	parent->addChild(this);
}

SimpleComboBox::~SimpleComboBox() {
	gtk_widget_destroy(_comboBox);
}

void SimpleComboBox::addSelection(string label, long value) {
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(_comboBox), NULL
		, label.c_str());
	_selections.push_back(value);
}

GtkWidget* SimpleComboBox::getWidget() {	
	return _comboBox;
}

// Sets the default selected value
void SimpleComboBox::setSelectedValue(long value) {
}

void SimpleComboBox::sendSelectedValue() {
	
}

size_t SimpleComboBox::getNVals() {
	return _selections.size();
}


