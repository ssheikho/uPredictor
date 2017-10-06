#include "KinectRecGUI.h"

KinectRecGUI::KinectRecGUI(LayoutContainer *parent, KinectRecorder &kr) :
_rl(parent, 100, 25)
, _filenameL(L"Filename:", &_rl, false, 75)
, _filenameE(L"D:\\\\W\\", &_rl, true, 150)
, _recdB(L"Record", &_rl, (IntSwitch *)&kr, 0, 75)
, _saveB(L"Stop", &_rl, (IntSwitch *)&kr, 1, 75)
{}

KinectRecGUI::~KinectRecGUI() {}
