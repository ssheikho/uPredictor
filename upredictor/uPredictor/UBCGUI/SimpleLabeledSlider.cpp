#include "SimpleLabeledSlider.h"
#include "UBCUtil.h"

SimpleLabeledSlider::SimpleLabeledSlider(
	LayoutContainer *parent
	//, int w
	//, int rowH
	, gfloat minVal
	, gfloat maxVal
	, gfloat startVal
	//, double scaleVal
	, gint digits
	) : _ss(parent, minVal, maxVal, startVal, digits)
{
	GtkWidget *slider = _ss.getWidget();
	gtk_scale_add_mark(GTK_SCALE(slider), minVal, GTK_POS_TOP,
			   doubleToString(minVal, digits).c_str());
	gtk_scale_add_mark(GTK_SCALE(slider), maxVal, GTK_POS_TOP,
			   doubleToString(maxVal, digits).c_str());
	/*
	if (digits) {
		_ss.TypeBroadcaster<long>::addRecipient(&_curVal);
	} else {
		_ss.TypeBroadcaster<double>::addRecipient(&_curVal);
	}
	*/
}

SimpleLabeledSlider::~SimpleLabeledSlider() {
	_ss.~SimpleSlider();
}

GtkWidget *SimpleLabeledSlider::getWidget() {
	return _ss.getWidget();
}

SimpleSlider &SimpleLabeledSlider::getSS() {
	return _ss;
}
