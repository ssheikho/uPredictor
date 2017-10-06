#ifndef SIMPLE_LABELED_SLIDER_H
#define SIMPLE_LABELED_SLIDER_H

#include "ColumnLayout.h"
#include "EvenlySpacedRow.h"
#include "LayoutElement.h"
#include "SimpleSlider.h"
#include "UBCEntry.h"

#include <memory>

using namespace std;

class IntValueArray;

class SimpleLabeledSlider : public LayoutElement {
public:
	SimpleLabeledSlider(
		IntValueArray *controlled, int controlledIndex, bool deleteIVAAtEnd,
		LayoutContainer *parent, int w, int rowH);
	~SimpleLabeledSlider();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

protected:
	IntValueArray *_controlled;
	ColumnLayout _cl;
	SimpleSlider _ss;
	EvenlySpacedRow _esr;
	UBCEntry _minVal, _curVal, _maxVal;
};

#endif