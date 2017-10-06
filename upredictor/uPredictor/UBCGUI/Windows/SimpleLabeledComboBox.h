#ifndef SIMPLE_LABELED_COMBO_BOX_H
#define SIMPLE_LABELED_COMBO_BOX_H

#include "LayoutElement.h"
#include "RowLayout.h"
#include "SimpleComboBox.h"
#include "UBCEntry.h"

#include <memory>

using namespace std;

class SimpleLabeledComboBox : public LayoutElement {
public:
	SimpleLabeledComboBox(
		LayoutContainer *parent
		, int labelW
		, int comboW
		, int h
		, int hLine
		, wstring label
		);
	~SimpleLabeledComboBox();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	SimpleComboBox &getSCB();

protected:
	RowLayout _rl;
	UBCEntry _l;
	SimpleComboBox _scb;
};

#endif