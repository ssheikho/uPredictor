#include "TrackerUI.h"
#include "UBCEntry.h"

TrackerUI::TrackerUI(LayoutContainer *parent, dart::Pose &pose, int modelNo) :
	_modelNo(modelNo)
	, _cl(parent, 600, 25) {
	for(int i = 0; i < pose.getDimensions(); i++) addRow(i);
}

TrackerUI::~TrackerUI() {}

void TrackerUI::processType(dart::UBCDARTTracker *tracker) {
	dart::Pose &pose = tracker->getPose(_modelNo);
	float *f = pose.getArticulation();
	for(int i = 0; i < pose.getDimensions(); i++) {
		_entries[i]->setTextD(f[i]);
	}
}

void TrackerUI::onStartup() {}

void TrackerUI::addRow(int i) {
	UBCEntry *e = new UBCEntry("-", &_cl, true, 100);
	_entries.push_back(e);
}
