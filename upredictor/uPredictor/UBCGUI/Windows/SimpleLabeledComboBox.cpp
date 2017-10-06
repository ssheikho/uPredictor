#include "SimpleLabeledComboBox.h"
#include "UBCUtil.h"

SimpleLabeledComboBox::SimpleLabeledComboBox(
	LayoutContainer *parent
	, int labelW
	, int comboW
	, int h
	, int hLine
	, wstring label
	) :
	_rl(parent, labelW + comboW, hLine)
	, _l(label.c_str(), &_rl, false, labelW, hLine)
	, _scb(&_rl, comboW, h, hLine) {}

SimpleLabeledComboBox::~SimpleLabeledComboBox() {}

int SimpleLabeledComboBox::getWidth() {
	return _rl.getWidth();
}

int SimpleLabeledComboBox::getHeight() {
	return _rl.getHeight();
}

void SimpleLabeledComboBox::setOrigin(int x, int y) {
	_rl.setOrigin(x, y);
}

void SimpleLabeledComboBox::updateSizeAllotment(int w, int h) {
	_rl.updateSizeAllotment(w, h);
}

HWND SimpleLabeledComboBox::getHWND() {
	return _rl.getHWND();
}

HINSTANCE SimpleLabeledComboBox::getHInstance() {
	return _rl.getHInstance();
}

SimpleComboBox &SimpleLabeledComboBox::getSCB() {
	return _scb;
}