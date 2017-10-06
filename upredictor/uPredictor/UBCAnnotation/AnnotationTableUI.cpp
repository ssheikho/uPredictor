#include "AnnotationTableUI.h"
#include "AnnotationClass.h"
#include "AnnotationClassTable.h"
#include "AnnotationObjectUI.h"
#include "AnnotationTable.h"
#include "RecNameCollection.h"
#include "UBCButton.h"
#include "UBCUtil.h"

AnnotationTableUI::AnnotationTableUI(
	AnnotationTable *at
	, AnnotationUIFactory *auif
	, RecNameCollection &rnc
	, LayoutContainer *parent) :
	_at(at),
	_cl(parent, 800, 100),
	_saveRow(&_cl, 800, 25),
	_buttonRow(&_cl, 800, 25),
	_fileL("Filename:", &_saveRow, false, 100, 25),
	_fileE(wstringToString(rnc.getDefaultAnnotationFilename()), &_saveRow, true,  400, 25),
	_saveButton("Save", &_saveRow, this, -1, 50, 25),
	_loadButton("Load", &_saveRow, this, -2, 50, 25),
	_clearButton("Clear", &_saveRow, this, -3, 50, 25),
	_sw(&_cl, 800, 500),
	_clObjs(&_sw, 800, 500), _auif(auif) {
	AnnotationClassTable *act = _at->getACT();
	int nClasses = act->getNClases();
	for (int i = 0; i < nClasses; i++) {
		int classID = act->getClassIDByIndex(i);
		AnnotationClass *ac = act->getClassByID(classID);
		string classNameS = ac->getName();
		wstring className = stringToWString(classNameS);// ac->getName();
		UBCButton *b = new UBCButton(
			classNameS, &_buttonRow, this, classID, 100, 25);
	}
	//act->getClassByID();
	_at->addListener(this);
}

AnnotationTableUI::~AnnotationTableUI(){}

void AnnotationTableUI::clearAnnotations() {
	// _clObjs.clear();
	// No clear function for column layout
	for (int i = 0; i < _objectUI.size(); i++) delete _objectUI[i];
	_objectUI.clear();
}

void AnnotationTableUI::addAnnotationObject(AnnotationTable *at, AnnotationObject *ao) {
	AnnotationObjectUI *aoui = new AnnotationObjectUI(ao, &_clObjs, _auif);
	_objectUI.push_back(aoui);
}

void AnnotationTableUI::clearAnnotationObjects(AnnotationTable *at) {
	clearAnnotations();
}

void AnnotationTableUI::updateSwitch(int val) {
	switch (val) {
	case -1:
		save();
		break;
	case -2:
		_at->clear();
		load();
		break;
	case -3:
		_at->clear();
		break;
	default:
		_at->addNew(val);
	}
}

void AnnotationTableUI::save() {
	fstream f;
	f.open(_fileE.getTextS(), ios::binary | ios::trunc | ios::out);
	_at->save(f);
}

void AnnotationTableUI::load() {
	fstream f;
	f.open(_fileE.getTextS(), ios::binary | ios::in);
	_at->load(f);
}