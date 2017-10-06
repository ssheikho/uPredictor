#include "AnnotationEnumUI.h"
#include "AnnotationEnumType.h"
#include "AnnotationIntValue.h"
#include "LayoutContainer.h"
#include "UBCUtil.h"

//#include <CommCtrl.h>

#include <codecvt>

AnnotationEnumUI::AnnotationEnumUI(
	AnnotationIntValue *aiv,
	LayoutContainer *parent) : _parent(parent),
	_aiv(aiv), _aet((AnnotationEnumType *)_aiv->getType()) {

	_comboBox = gtk_combo_box_text_new();
	updateFromValue();
	parent->addChild(this);
}

AnnotationEnumUI::~AnnotationEnumUI() {
	gtk_widget_destroy(_comboBox);
}

void AnnotationEnumUI::updateFromCurSel() {
}

void AnnotationEnumUI::updateFromValue() {
}

GtkWidget *AnnotationEnumUI::getWidget() {
	return _comboBox;
}