#include "PauseUnpauseUI.h"
#include "Pause.h"

PauseUnpauseUI::PauseUnpauseUI(IntSwitch *pause, LayoutContainer *parent) :
	_rl(parent, 200, 25)
	, _pb(L"PAUSE", &_rl, pause, 0, 100, 25)
	, _ub(L"UNPAUSE", &_rl, pause, 1, 100, 25)
	, _ksb(L"Kickstart", &_rl, pause, 2, 100, 25) {}

PauseUnpauseUI::~PauseUnpauseUI() {}