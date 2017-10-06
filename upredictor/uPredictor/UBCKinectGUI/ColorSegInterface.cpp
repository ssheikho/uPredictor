#include "ColorSegInterface.h"
#include "ColorBlobDetector.h"
#include "ColorBlobParams.h"
#include "ProcessingParameters.h"

#define LABEL_WIDTH 135

ColorSegInterface::ColorSegInterface(
	LayoutContainer *parent
	, ColorBlobDetector *cbd
	) :
	_cl(parent, 100, 255)
	, _nameRL(&_cl, 100, 25)
	, _nameL(L"Tracker Name", &_nameRL, false, LABEL_WIDTH)
	, _nameE(cbd->getCBP().getName(), &_nameRL, true, LABEL_WIDTH)
	, _glColors(&_cl, LABEL_WIDTH * 3, 25)
	//, _scbDisplayChannel(&_cl, 200, 400, 200, 25, L"Display Channel")
	, _scbMajorityChannel(&_cl, 200, 400, 200, 25, L"Majority Channel")
	, _gl(&_cl, 1200, 25)
	, _icb(0, 0)
{
	//Color selection interface
	_glColors.addRow();
	_colCur = new UBCEntry(L"Current", &_glColors, false, LABEL_WIDTH);
	_minMargL = new UBCEntry(L"Min Margin", &_glColors, false, LABEL_WIDTH);
	_maxMargL = new UBCEntry(L"Max Margin", &_glColors, false, LABEL_WIDTH);
	_glColors.addRow();
	_crCur = new ColorRow(&_glColors);
	_minMargE = new UBCEntry(L"0", &_glColors, true, LABEL_WIDTH);
	_maxMargE = new UBCEntry(L"0", &_glColors, true, LABEL_WIDTH);
//	_rectB = new UBCButton(L"Spanning Rect", &_glColors, );

	_glColors.addRow();
	_colMin = new UBCEntry(L"Min", &_glColors, false, LABEL_WIDTH);
	_colMax = new UBCEntry(L"Max", &_glColors, false, LABEL_WIDTH);
	_glColors.addRow();
	_crMin = new ColorRow(&_glColors);
	_crMax = new ColorRow(&_glColors);

	//_scbDisplayChannel.getSCB().addRecipient(&_icb._index);
	//cbd->populateVideoChannelCB(&_scbDisplayChannel.getSCB());
	//cbd->TypeBroadcaster<ImageChannelProvider *>::addRecipient(&_icb);

	ColorBlobParams &cbp = cbd->getCBP();

	_scbMajorityChannel.getSCB().addRecipient(
		&cbp._majorityColorChannel);
	cbd->populateBGRChannelCB(&_scbMajorityChannel.getSCB());

	//_gl.addRow();
	//_gradientL = new UBCEntry(L"Gradient", &_gl, false, 100);
	//_gradientThresh = new SimpleLabeledSlider(&_gl, 300, 25
	//	, 0, 5000, 0, 100.0, false);

	_gl.addRow();
	_bMinusGL = new UBCEntry(L"B Minus G", &_gl, false, 100);
	_bMinusGThresh = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);
	_bMinusRL = new UBCEntry(L"B Minus R", &_gl, false, 100);
	_bMinusRThresh = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);

	_gl.addRow();
	_gMinusBL = new UBCEntry(L"G Minus B", &_gl, false, 100);
	_gMinusBThresh = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);
	_gMinusRL = new UBCEntry(L"G Minus R", &_gl, false, 100);
	_gMinusRThresh = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);

	_gl.addRow();
	_rMinusBL = new UBCEntry(L"R Minus B", &_gl, false, 100);
	_rMinusBThresh = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);
	_rMinusGL = new UBCEntry(L"R Minus G", &_gl, false, 100);
	_rMinusGThresh = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);

	_gl.addRow();
	_minPtsL = new UBCEntry(L"Min Pts", &_gl, false, 100);
	_minPtsThresh = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);

	_gl.addRow();
	_drawBL = new UBCEntry(L"Draw B", &_gl, false, 100);
	_drawB = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);
	_drawGL = new UBCEntry(L"Draw G", &_gl, false, 100);
	_drawG = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);
	_drawRL = new UBCEntry(L"Draw R", &_gl, false, 100);
	_drawR = new SimpleLabeledSlider(&_gl, 300, 25, 0, 255, 0);

	_bMinusGThresh->getSS().TypeBroadcaster<long>::addRecipient(
		&cbp._bMinusGThresh);
	_bMinusRThresh->getSS().TypeBroadcaster<long>::addRecipient
		(&cbp._bMinusRThresh);

	_gMinusBThresh->getSS().TypeBroadcaster<long>::addRecipient(
		&cbp._gMinusBThresh);
	_gMinusRThresh->getSS().TypeBroadcaster<long>::addRecipient(
		&cbp._gMinusRThresh);

	_rMinusBThresh->getSS().TypeBroadcaster<long>::addRecipient(
		&cbp._rMinusBThresh);
	_rMinusGThresh->getSS().TypeBroadcaster<long>::addRecipient
		(&cbp._rMinusGThresh);

	_minPtsThresh->getSS().TypeBroadcaster<long>::addRecipient
		(&cbp._minBlobPts);

	//_gradientThresh->getSS().TypeBroadcaster<double>::addRecipient
	//	(&cbp._gradientThresh);

	_drawB->getSS().TypeBroadcaster<long>::addRecipient(&cbp._drawB);
	_drawG->getSS().TypeBroadcaster<long>::addRecipient(&cbp._drawG);
	_drawR->getSS().TypeBroadcaster<long>::addRecipient(&cbp._drawR);
}

ColorSegInterface::~ColorSegInterface() {}

ImageChannelBroadcaster &ColorSegInterface::getICB() {
	return _icb;
}

int ColorSegInterface::getWidth() {
	return _gl.getWidth();
}

int ColorSegInterface::getHeight() {
	return _gl.getHeight();
}

void ColorSegInterface::setOrigin(int x, int y) {
	return _gl.setOrigin(x, y);
}

void ColorSegInterface::updateSizeAllotment(int w, int h) {
	return _gl.updateSizeAllotment(w, h);
}

HWND ColorSegInterface::getHWND() {
	return _gl.getHWND();
}

HINSTANCE ColorSegInterface::getHInstance() {
	return _gl.getHInstance();
}

void ColorSegInterface::processType(cv::Scalar t) {
	_crCur->processType(t);
}

void ColorSegInterface::processType(pair<cv::Scalar, cv::Scalar> t) {
	_crMin->processType(t.first);
	_crMax->processType(t.second);
}

void ColorSegInterface::processType(pair<uint8_t, uint8_t> t) {
	_minMargE->setTextI(t.first);
	_maxMargE->setTextI(t.second);
}

void ColorSegInterface::updateSwitch(int val) {}