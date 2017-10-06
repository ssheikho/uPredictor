#ifndef PAUSE_UNPAUSE_UI_H
#define PAUSE_UNPAUSE_UI_H

#include "RowLayout.h"
#include "UBCButton.h"

class Pause;

class PauseUnpauseUI {
public:
	PauseUnpauseUI(IntSwitch *pause, LayoutContainer *parent);
	~PauseUnpauseUI();

protected:
	RowLayout _rl;
	UBCButton _pb, _ub, _ksb;
};

#endif
