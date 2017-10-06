#include "SimpleLabeledComboBox.h"
#include "UBCUtil.h"

SimpleLabeledComboBox::SimpleLabeledComboBox(
	LayoutContainer *parent
	//, int labelW
	//, int comboW
	//, int h
	//, int hLine
	, string label
	) :
	_rl(parent, 0, 0)
	, _l(label, &_rl, false, 0, 0)
	, _scb(&_rl) {}

SimpleLabeledComboBox::~SimpleLabeledComboBox() {
	_rl.~RowLayout();
}

GtkWidget *SimpleLabeledComboBox::getWidget() {
	return _rl.getWidget();
}

SimpleComboBox &SimpleLabeledComboBox::getSCB() {
	return _scb;
}
