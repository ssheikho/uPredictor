#ifndef KINECT_REC_GUI_H
#define KINECT_REC_GUI_H

#include "RowLayout.h"
#include "UBCButton.h"
#include "UBCEntry.h"

class KinectRecorder;

class KinectRecGUI {
public:
	KinectRecGUI(LayoutContainer *parent, KinectRecorder &kr);
	~KinectRecGUI();

protected:
	RowLayout _rl;
	UBCEntry _filenameL, _filenameE;
	UBCButton _recdB, _saveB;
};
#endif