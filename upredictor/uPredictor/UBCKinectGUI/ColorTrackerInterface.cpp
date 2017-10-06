#include "ColorTrackerInterface.h"
#include "ColorBlobDetector.h"
#include "ColorSegInterface.h"
#include "ColorTracker.h"
#include "ImageWindow.h"

ColorTrackerInterface::ColorTrackerInterface(
	LayoutContainer *parent
	, ColorTracker &ct
	, ImageWindow &iw
	) :
	_ct(ct)
	, _topLevelColumn(parent, 100, 25)
	, _buttonRowOne(&_topLevelColumn, 100, 25)
	, _buttonRowTwo(&_topLevelColumn, 100, 25)
	, _sw(&_topLevelColumn, 1800, 500)
	, _cl(&_sw, 100, 25)
	, _loadButton(L"Load", &_buttonRowOne, this, 1, 100, 25)
	, _saveButton(L"Save", &_buttonRowOne, this, 2, 100, 25)
	, _fileNameL(L"Filename: ", &_buttonRowOne, false, 100, 25)
	, _fileNameE(L"D:\color_track_config.bin", &_buttonRowOne, false, 300, 25)
	, _addButton(L"Add", &_buttonRowTwo, this, 0, 100, 25)
	, _addE(L"DEFAULT_TRACK_NAME", &_buttonRowTwo, true, 200, 25)
	, _slcb(&_buttonRowTwo, 200, 200, 300, 25, L"Display from tracker:")
{
	iw.TypeBroadcaster<pair<int, int>>::addRecipient(&ct.getTRIntInt());
	iw.TypeBroadcaster<DragRect>::addRecipient(&ct.getTRDragRect());
	_slcb.getSCB().addRecipient(&_ct.getTBCS()._curChan);

	_slcb.getSCB().addSelection(L"COLOR TRACKS", _slcb.getSCB().getNVals());
}

ColorTrackerInterface::~ColorTrackerInterface() {}

//public LayoutElement
int ColorTrackerInterface::getWidth() {
	return _cl.getWidth();
}

int ColorTrackerInterface::getHeight() {
	return _cl.getHeight();
}

void ColorTrackerInterface::setOrigin(int x, int y) {
	return _cl.setOrigin(x, y);
}

void ColorTrackerInterface::updateSizeAllotment(int w, int h) {
	return _cl.updateSizeAllotment(w, h);
}

HWND ColorTrackerInterface::getHWND() {
	return _cl.getHWND();
}

HINSTANCE ColorTrackerInterface::getHInstance() {
	return _cl.getHInstance();
}

//public IntSwitch
void ColorTrackerInterface::updateSwitch(int val) {
	switch (val) {
	case 0:
	{
		wstring name = _addE.getTextW();
		ColorBlobDetector *cbd = _ct.add(name);
		ColorSegInterface *csi = new ColorSegInterface(&_cl, cbd);
		_slcb.getSCB().addSelection(name, _slcb.getSCB().getNVals());
	}
		break;
	case 1:
		_ct.load(_fileNameE.getTextW());
		break;
	case 2:
		_ct.save(_fileNameE.getTextW());
		break;
	}
}