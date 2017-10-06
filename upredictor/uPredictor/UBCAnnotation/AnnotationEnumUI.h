#ifndef ANNOTATION_ENUM_UI_H
#define ANNOTATION_ENUM_UI_H

#include "LayoutElement.h"

#include <map>

using namespace std;

class AnnotationEnumType;
class AnnotationIntValue;
class LayoutContainer;

class AnnotationEnumUI :
	public LayoutElement {
public:
	AnnotationEnumUI(AnnotationIntValue *aiv, LayoutContainer *parent);
	virtual ~AnnotationEnumUI();

	void updateFromCurSel();
	void updateFromValue();

	//LayoutElement
	GtkWidget *getWidget();

protected:

	LayoutContainer *_parent;
	AnnotationIntValue *_aiv;
	AnnotationEnumType *_aet;
	GtkWidget* _comboBox;
};

#endif
