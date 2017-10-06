#include "UBCEntry.h"
//#include "IntegerIndicator.h"
//#include "IntValueArray.h"
#include "LayoutContainer.h"
#include "UBCUtil.h"

#include <cstdlib>

UBCEntry::UBCEntry(string text, LayoutContainer *parent,
	bool entry,	int w, int h) :
	_text(text),
	_parent(parent) //_x(0), _y(0), _w(w), _h(h)
	, _valIsStored(false)
	//, _ivaIndex(-1), _minValMax(-1)
{
	_entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(_entry), text.c_str());
	gtk_editable_set_editable(GTK_EDITABLE(_entry), entry);

	parent->addChild(this);
}

UBCEntry::~UBCEntry() {
	gtk_widget_destroy(_entry);
}

GtkWidget *UBCEntry::getWidget() {
	return _entry;
}

string UBCEntry::getTextS() {
	return _text;
}

double UBCEntry::getTextD() {
	return strtod(_text.c_str(), NULL);
}

void UBCEntry::setTextD(double d, int precision) {
	_text = doubleToString(d, precision);
	//if (!_valIsStored)
	gtk_entry_set_text(GTK_ENTRY(_entry), _text.c_str());
	//_valIsStored = true;
}

void UBCEntry::setTextI(long i) {
	_text = intToString(i);
	//if(!_valIsStored)
	gtk_entry_set_text(GTK_ENTRY(_entry), _text.c_str());
	//_valIsStored = true;
}

/*
void UBCEntry::processType(double t) {
	setTextD(t, 3);
}

void UBCEntry::processType(long t) {
	setTextI(t);
}
*/

