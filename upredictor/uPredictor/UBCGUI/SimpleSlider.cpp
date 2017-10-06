#include "SimpleSlider.h"
#include "LayoutContainer.h"

#include <cmath>
#include <iostream>

void SimpleSlider::valueChanged(
	GtkAdjustment *adjustment, gpointer user_data) {
	gdouble pos =
		gtk_range_get_value(
			GTK_RANGE(((SimpleSlider *)user_data)->_slider));
	((SimpleSlider *)user_data)->TypeBroadcaster<double>::fireUpdate(pos);
	((SimpleSlider *)user_data)->TypeBroadcaster<long>::fireUpdate(pos);
}

SimpleSlider::SimpleSlider(
	LayoutContainer *parent
	, gfloat minVal
	, gfloat maxVal
	, gfloat startVal
	//, gfloat step
	, gint digits
	//, gfloat pageSize = 1.0
)
	//_minVal(minVal), _maxVal(maxVal)
{
	//minimum and maximum value of the slider 
	_adjustent = gtk_adjustment_new(startVal, minVal, maxVal
		, 1.0/(double)std::pow(10,digits)
		, 1.0/(double)std::pow(10,digits)
		, 1.0/(double)std::pow(10,digits)
		);

	_slider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, _adjustent);
	slider_set_default_values(GTK_SCALE (_slider), digits);
	gtk_scale_add_mark(GTK_SCALE (_slider), minVal, GTK_POS_LEFT, NULL);
	gtk_scale_add_mark(GTK_SCALE (_slider), maxVal, GTK_POS_RIGHT, NULL);

	g_signal_connect(_slider, "value-changed", G_CALLBACK(valueChanged)
		, (gpointer)this);

	set(startVal);
	//updateFromSrc();
	parent->addChild(this);
	//gtk_widget_show (_slider);
}

SimpleSlider::~SimpleSlider() {
	gtk_widget_destroy(_slider);
}


void SimpleSlider::slider_set_default_values(GtkScale *scale, gint digits) {
	gtk_scale_set_digits(scale, digits);
	gtk_scale_set_value_pos(scale, GTK_POS_BOTTOM);
	gtk_scale_set_draw_value(scale, TRUE);
}

void SimpleSlider::set(GtkWidget *slider, GtkPositionType  pos ){
	//Sets the position in which the current value is displayed.
	gtk_scale_set_value_pos (GTK_SCALE (slider), pos);
}

GtkWidget *SimpleSlider::getWidget() {
	return _slider;	
}

double SimpleSlider::get() {
	return gtk_adjustment_get_value(_adjustent);
}

void SimpleSlider::set(double val) {
	gtk_adjustment_set_value(_adjustent, val);
}

void SimpleSlider::updateFromSlider() {
	gdouble val = gtk_adjustment_get_value(_adjustent);
	TypeBroadcaster<long>::fireUpdate(val);
	TypeBroadcaster<double>::fireUpdate(val);
}
