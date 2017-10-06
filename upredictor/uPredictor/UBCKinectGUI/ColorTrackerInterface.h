#ifndef COLOR_TRACKER_INTERFACE_H
#define COLOR_TRACKER_INTERFACE_H

#include "ColumnLayout.h"
#include "IntSwitch.h"
#include "RowLayout.h"
#include "ScrollingWindow.h"
#include "SimpleLabeledComboBox.h"
#include "TypeRecipientChannelSelector.h"
#include "UBCButton.h"
#include "UBCEntry.h"

#include <vector>



class ColorSegInterface;
class ColorTracker;
class ColorTrackerConfiguration;
class ImageWindow;

class ColorTrackerInterface :
	public LayoutElement
	, public IntSwitch {

public:
	ColorTrackerInterface(
		LayoutContainer *parent
		, ColorTracker &ct
		, ImageWindow &iw
		);
	~ColorTrackerInterface();

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
	ColorTracker &_ct;
	ColumnLayout _topLevelColumn;
	RowLayout _buttonRowOne, _buttonRowTwo;
	ScrollingWindow _sw;
	ColumnLayout _cl;
	UBCButton _loadButton, _saveButton;
	UBCEntry _fileNameL, _fileNameE;
	UBCButton _addButton;
	UBCEntry _addE;
	SimpleLabeledComboBox _slcb;
	vector<ColorSegInterface *> _csi;
};

#endif