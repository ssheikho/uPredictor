#include "ColorRow.h"

#define COLOR_LABEL_WIDTH 15
#define COLOR_ENTRY_WIDTH 30

ColorRow::ColorRow(
	LayoutContainer *parent
	) :
	_rlColor(parent, 135, 25)
	, _bL("B", &_rlColor, false, COLOR_LABEL_WIDTH)
	, _bE("0", &_rlColor, true, COLOR_ENTRY_WIDTH)
	, _gL("G", &_rlColor, false, COLOR_LABEL_WIDTH)
	, _gE("0", &_rlColor, true, COLOR_ENTRY_WIDTH)
	, _rL("R", &_rlColor, false, COLOR_LABEL_WIDTH)
	, _rE("0", &_rlColor, true, COLOR_ENTRY_WIDTH) {}

ColorRow::~ColorRow() {
	_rlColor.~RowLayout();
}

//LayoutElement
GtkWidget *ColorRow::getWidget() {
	return _rlColor.getWidget();
}

void ColorRow::processType(cv::Scalar t) {
	long b = t[0];
	long g = t[1];
	long r = t[2];
	_bE.setTextI(b);
	_gE.setTextI(g);
	_rE.setTextI(r);
}

void ColorRow::onStartup() {}
