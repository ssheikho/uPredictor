#include "AnnotationObjectUI.h"
#include "AnnotationClass.h"
#include "AnnotationObject.h"
#include "AnnotationType.h"
#include "AnnotationUIFactory.h"
#include "GridLayout.h"
#include "UBCEntry.h"

#include <codecvt>

AnnotationObjectUI::AnnotationObjectUI(AnnotationObject *ao,
	LayoutContainer *parent, AnnotationUIFactory *auif) : _ao(ao),
	_gl(parent, 10, 10) {
	// wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

	AnnotationClass *ac = _ao->getClass();
	int nFields = ac->getNFields();
	for (int field = 0; field < nFields; field++) {
		AnnotationType *at = ac->getFieldType(field);
		wstring name = ac->getFieldNameW(field);
		_gl.addRow();
		string cName(name.begin(), name.end());
		UBCEntry *label =
			new UBCEntry(cName, &_gl, false, 100, 25);
		_labels.push_back(label);

		AnnotationValue *av = ao->getAV(field);
		LayoutElement *ui = auif->createUI(av, &_gl);
		_ui.push_back(ui);
	}

	//parent->addChild(this);
}

AnnotationObjectUI::~AnnotationObjectUI() {
	for (int i = 0; i < _labels.size(); i++) {
		UBCEntry *are = _labels[i];
		LayoutElement *le = _ui[i];
		delete are;
		delete le;
	}

	_labels.clear();
	_ui.clear();
}