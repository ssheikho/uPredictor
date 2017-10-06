#ifndef SIMPLE_LABELED_SLIDER_H
#define SIMPLE_LABELED_SLIDER_H

#include "LayoutElement.h"
#include "SimpleSlider.h"

#include <memory>

using namespace std;

class SimpleLabeledSlider : public LayoutElement {
public:
	SimpleLabeledSlider(
		LayoutContainer *parent
		//, int w
		//, int rowH
		, gfloat minVal
		, gfloat maxVal
		, gfloat startVal
		//, double scaleVal = 1.0
		, gint digits
		);
	~SimpleLabeledSlider();

	GtkWidget *getWidget();
	SimpleSlider &getSS();

protected:
	SimpleSlider _ss;
};

#endif
