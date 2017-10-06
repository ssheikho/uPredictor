#ifndef SIMPLE_LABELED_SLIDER_H
#define SIMPLE_LABELED_SLIDER_H

#include "ColumnLayout.h"
#include "EvenlySpacedRow.h"
#include "LayoutElement.h"
#include "SimpleSlider.h"
#include "UBCEntry.h"

#include <memory>

using namespace std;

class SimpleLabeledSlider : public LayoutElement {
public:
	SimpleLabeledSlider(
		LayoutContainer *parent
		, int w
		, int rowH
		, long minVal
		, long maxVal
		, long startVal
		, double scaleVal = 1.0
		, bool isInt = true
		);
	~SimpleLabeledSlider();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	SimpleSlider &getSS();

protected:
	ColumnLayout _cl;
	SimpleSlider _ss;
	EvenlySpacedRow _esr;
	UBCEntry _minVal, _curVal, _maxVal;
};

#endif