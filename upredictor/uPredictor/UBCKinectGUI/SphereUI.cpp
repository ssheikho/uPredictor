#include "SphereUI.h"
#include "SimpleLabeledSlider.h"
#include "UBCEntry.h"
#include "UBCSphere.h"

#define LABEL_WIDTH 135

SphereUI::SphereUI(
	LayoutContainer *parent
	, UBCSphere &sphere) :
	_gl(parent, 1200, 25) {
	_gl.addRow();
	_xL = new UBCEntry(L"X", &_gl, false, LABEL_WIDTH);
	_slsX = new SimpleLabeledSlider(&_gl, 1000, 25, -10000, 10000, 0, 100.0, false);

	_gl.addRow();
	_yL = new UBCEntry(L"Y", &_gl, false, LABEL_WIDTH);
	_slsY = new SimpleLabeledSlider(&_gl, 1000, 25, -10000, 10000, 0, 100.0, false);

	_gl.addRow();
	_zL = new UBCEntry(L"Z", &_gl, false, LABEL_WIDTH);
	_slsZ = new SimpleLabeledSlider(&_gl, 1000, 25, -10000, 10000, 0, 100.0, false);

	_gl.addRow();
	_rL = new UBCEntry(L"R", &_gl, false, LABEL_WIDTH);
	_slsR = new SimpleLabeledSlider(&_gl, 1000, 25, -10000, 10000, 0, 100.0, false);

	_slsX->getSS().TypeBroadcaster<double>::addRecipient(&sphere._x);
	_slsY->getSS().TypeBroadcaster<double>::addRecipient(&sphere._y);
	_slsZ->getSS().TypeBroadcaster<double>::addRecipient(&sphere._z);
	_slsR->getSS().TypeBroadcaster<double>::addRecipient(&sphere._r);

}

SphereUI::~SphereUI() {}