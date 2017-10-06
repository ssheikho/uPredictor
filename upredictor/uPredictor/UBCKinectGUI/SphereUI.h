#ifndef SPHERE_UI_H
#define SPHERE_UI_H

#include "GridLayout.h"

class SimpleLabeledSlider;
class UBCEntry;
class UBCSphere;

class SphereUI {
public:
	SphereUI(
		LayoutContainer *parent
		, UBCSphere &sphere
		);
	~SphereUI();

protected:
	GridLayout _gl;
	UBCEntry *_xL, *_yL, *_zL, *_rL;
	SimpleLabeledSlider	*_slsX, *_slsY, *_slsZ, *_slsR;
};

#endif