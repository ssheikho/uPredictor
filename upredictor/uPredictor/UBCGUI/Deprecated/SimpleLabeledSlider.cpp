#include "SimpleLabeledSlider.h"

SimpleLabeledSlider::SimpleLabeledSlider(
	IntValueArray *controlled, int controlledIndex, bool deleteIVAAtEnd,
	LayoutContainer *parent, int w, int rowH) :
	_controlled(controlled),
	_cl(parent, w, 0),
	_ss(&_cl, w, rowH, controlled, controlledIndex, deleteIVAAtEnd, NULL, 0),
	_esr(&_cl, w, rowH),
	_minVal(L"0", &_esr, false, 50),
	_curVal(L"0", &_esr, false, 50),
	_maxVal(L"0", &_esr, false, 50) {
	_minVal.listenToIVA(controlled, controlledIndex, 0);
	_curVal.listenToIVA(&_ss, 0, 1);
	_maxVal.listenToIVA(controlled, controlledIndex, 2);
}

SimpleLabeledSlider::~SimpleLabeledSlider() {
	_controlled->removeIVAListener(&_minVal);
	_controlled->removeIVAListener(&_curVal);
	_controlled->removeIVAListener(&_maxVal);
}

int SimpleLabeledSlider::getWidth() {
	return _cl.getWidth();
}

int SimpleLabeledSlider::getHeight() {
	return _cl.getHeight();
}

void SimpleLabeledSlider::setOrigin(int x, int y) {
	_cl.setOrigin(x, y);
}

void SimpleLabeledSlider::updateSizeAllotment(int w, int h) {
	_cl.updateSizeAllotment(w, h);
}

HWND SimpleLabeledSlider::getHWND() {
	return _cl.getHWND();
}

HINSTANCE SimpleLabeledSlider::getHInstance() {
	return _cl.getHInstance();
}