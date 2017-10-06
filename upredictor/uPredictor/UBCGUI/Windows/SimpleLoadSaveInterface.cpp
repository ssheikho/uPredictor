#include "SimpleLoadSaveInterface.h"
#include "SimpleLoadSave.h"

SimpleLoadSaveInterface::SimpleLoadSaveInterface(
	LayoutContainer *parent
	, int h
	, wstring fileNameLabel
	, wstring defaultFilename
	, SimpleLoadSave *sls) :
	_rl(parent, 10, h)
	, _filenameL(fileNameLabel, &_rl, false, 100, h)
	, _filenameE(defaultFilename, &_rl, true, 400, h)
	, _saveB(L"Save", &_rl, this, 0, 100, h)
	, _loadB(L"Load", &_rl, this, 1, 100, h)
	, _sls(sls)
{}

SimpleLoadSaveInterface::~SimpleLoadSaveInterface() {}

//public LayoutElement
int SimpleLoadSaveInterface::getWidth() {
	return _rl.getWidth();
}

int SimpleLoadSaveInterface::getHeight() {
	return _rl.getHeight();
}

void SimpleLoadSaveInterface::setOrigin(int x, int y) {
	return _rl.setOrigin(x, y);
}

void SimpleLoadSaveInterface::updateSizeAllotment(int w, int h) {
	return _rl.updateSizeAllotment(w, h);
}

HWND SimpleLoadSaveInterface::getHWND() {
	return _rl.getHWND();
}

HINSTANCE SimpleLoadSaveInterface::getHInstance() {
	return _rl.getHInstance();
}

//public IntSwitch
void SimpleLoadSaveInterface::updateSwitch(int val) {
	switch (val) {
	case 0:
		_sls->save(_filenameE.getTextW());
		break;
	case 1:
		_sls->load(_filenameE.getTextW());
		break;
	}
}