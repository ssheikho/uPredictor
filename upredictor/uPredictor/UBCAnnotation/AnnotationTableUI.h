#ifndef ANNOTATION_TABLE_UI_H
#define ANNOTATION_TABLE_UI_H

#include "AnnotationTableListener.h"
#include "AnnotationUIFactory.h"
#include "ColumnLayout.h"
#include "IntSwitch.h"
#include "RowLayout.h"
#include "ScrollingWindow.h"
#include "UBCButton.h"
#include "UBCEntry.h"

#include <vector>

class AnnotationObjectUI;
class AnnotationTable;
class AutoResizeButton;
class RecNameCollection;

class AnnotationTableUI : public AnnotationTableListener, public IntSwitch {
public:
	AnnotationTableUI(
		AnnotationTable *at,
		AnnotationUIFactory *auif,
		RecNameCollection &rnc,
		LayoutContainer *parent);
	~AnnotationTableUI();

	void clearAnnotations();

	//From AnnotationTableListener
	void addAnnotationObject(AnnotationTable *at, AnnotationObject *ao);
	void clearAnnotationObjects(AnnotationTable *at);

	//From IntSwitch
	void updateSwitch(int val);

protected:
	void save();
	void load();

	AnnotationTable *_at;
	ColumnLayout _cl;
	RowLayout _saveRow, _buttonRow;
	UBCEntry _fileL, _fileE;
	UBCButton _saveButton, _loadButton, _clearButton;
	ScrollingWindow _sw;
	ColumnLayout _clObjs;

	vector <AutoResizeButton *> _buttons;
	vector <AnnotationObjectUI *> _objectUI;

	AnnotationUIFactory *_auif;
};

#endif