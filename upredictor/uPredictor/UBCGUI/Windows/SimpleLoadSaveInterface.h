#ifndef SIMPLE_LOAD_SAVE_INTERFACE_H
#define SIMPLE_LOAD_SAVE_INTERFACE_H

#include "IntSwitch.h"
#include "RowLayout.h"
#include "UBCButton.h"
#include "UBCEntry.h"

class SimpleLoadSave;

class SimpleLoadSaveInterface :
	public LayoutElement
	, public IntSwitch
{
public:
	SimpleLoadSaveInterface(
		LayoutContainer *parent
		, int h
		, wstring fileNameLabel
		, wstring defaultFilename
		, SimpleLoadSave *sls);
	~SimpleLoadSaveInterface();

	//public LayoutElement
	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	//public IntSwitch
	void updateSwitch(int val);

protected:
	RowLayout _rl;
	UBCEntry _filenameL, _filenameE;
	UBCButton _saveB, _loadB;
	SimpleLoadSave *_sls;
};

#endif