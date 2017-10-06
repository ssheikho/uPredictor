#ifndef ANNOTATION_OBJECT_UI_H
#define ANNOTATION_OBJECT_UI_H

//JWH	NEEDS PORTING FOR GRIDLAYOUT

#include "GridLayout.h"

#include <vector>

using namespace std;

class AnnotationObject;
class AnnotationUIFactory;
class LayoutContainer;
class LayoutElement;
class UBCEntry;

class AnnotationObjectUI {
public:
	AnnotationObjectUI(AnnotationObject *ao, LayoutContainer *parent,
		AnnotationUIFactory *auif);
	~AnnotationObjectUI();

protected:
	AnnotationObject *_ao;
	GridLayout _gl;
	vector<UBCEntry *> _labels;
	vector<LayoutElement *> _ui;
};

#endif