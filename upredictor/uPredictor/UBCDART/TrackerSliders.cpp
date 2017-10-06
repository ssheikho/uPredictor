#include "TrackerSliders.h"
#include "SimpleSlider.h"

TrackerSliders::TrackerSliders(
	LayoutContainer *parent
	, dart::Pose &pose
) : _cl(parent, 100, 100), _pose(pose) {
	for(int i = 0; i < 3; i++) addRow(i);
	//for(int i = 0; i < _pose.getDimensions(); i++) addRow(i);
}

TrackerSliders::~TrackerSliders() {}

void TrackerSliders::addRow(int i) {
	SimpleSlider *e = new SimpleSlider(&_cl, -10.0f, 10.0f, 0.0f, 2);
	_sliders.push_back(e);
}

void TrackerSliders::processType(dart::UBCDARTTracker *tracker) {
	float f[3];
	for(int i = 0; i < 3; i++) f[i] = _sliders[i]->get();
	dart::SE3 &Tcm = _pose.getTransformCameraToModel();
	Tcm.setVals(f[0], f[1], f[2]);
	_pose.setTransformCameraToModel(Tcm);

	//float *f = _pose.getArticulation();
	//for(int i = 0; i < _pose.getDimensions(); i++) f[i] = _sliders[i]->get();
		
}

void TrackerSliders::onStartup() {
	
}
