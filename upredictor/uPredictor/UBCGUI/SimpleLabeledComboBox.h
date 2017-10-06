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
		//, int labelW
		//, int comboW
		//, int h
		//, int hLine
		, string label
		);
	~SimpleLabeledComboBox();

	GtkWidget *getWidget();
	SimpleComboBox &getSCB();

protected:
	RowLayout _rl;
	UBCEntry _l;
	SimpleComboBox _scb;
};

#endif
