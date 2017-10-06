#ifndef SIMPLE_SLIDER_H
#define SIMPLE_SLIDER_H

#include "LayoutElement.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <map>
#include <memory>

using namespace std;

class IntValueArray;
class LayoutContainer;

class SimpleSlider :
	//public TypeRecipient<long>
	public TypeBroadcaster<long>
	//, public TypeRecipient<double>
	, public TypeBroadcaster<double>
	, public LayoutElement
{
public:
	SimpleSlider(
		LayoutContainer *parent
		//, int w
		//, int h
		, gfloat minVal
		, gfloat maxValg
		, gfloat startVal
		//, gfloat step
		, gint digits
		//, gfloat pageSize = 1.0
		);
	virtual ~SimpleSlider();
    

	void updateFromSlider();
	
	GtkWidget *getWidget();

	double get();
	void set(double val);

	
	static void valueChanged(GtkAdjustment *adjustment, gpointer user_data);

protected:
	//Set the value position on slider
	void slider_set_default_values(GtkScale *scale, gint digits);

	//Set the update policy
	void set(GtkWidget *slider, GtkPositionType  pos );

	//Set the number of decimal places

	GtkAdjustment *_adjustent;
	GtkWidget *_slider;
};

#endif
