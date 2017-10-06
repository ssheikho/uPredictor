#include "SimpleLabeledSlider.h"
#include "UBCUtil.h"

SimpleLabeledSlider::SimpleLabeledSlider(
	LayoutContainer *parent
	, int w
	, int rowH
	, long minVal
	, long maxVal
	, long startVal
	, double scaleVal
	, bool isInt
	) :
	_cl(parent, w, 0),
	_ss(&_cl, w, rowH, minVal, maxVal, startVal, scaleVal),
	_esr(&_cl, w, rowH),
	_minVal(
		isInt ?
		thingToWString<long>(minVal, 0) :
		thingToWString<double>((double)minVal / scaleVal, 3)
		, &_esr, false, 50),
	_curVal(
		isInt ?
		thingToWString<long>(startVal, 0) :
		thingToWString<double>((double)startVal / scaleVal, 3)
		, &_esr, false, 50),
	_maxVal(
		isInt ?
		thingToWString<long>(maxVal, 0) :
		thingToWString<double>((double)maxVal / scaleVal, 3)
		, &_esr, false, 50) {
	if (isInt) {
		_ss.TypeBroadcaster<long>::addRecipient(&_curVal);
	} else {
		_ss.TypeBroadcaster<double>::addRecipient(&_curVal);
	}
}

SimpleLabeledSlider::~SimpleLabeledSlider() {}

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

SimpleSlider &SimpleLabeledSlider::getSS() {
	return _ss;
}