#ifndef TRACKER_SLIDERS_H
#define TRACKER_SLIDERS_H

#include "ColumnLayout.h"
#include "TypeRecipient.h"
#include "UBCDARTTracker.h"

#include "pose/pose.h"

class SimpleSlider;

class TrackerSliders :
	public TypeRecipient<dart::UBCDARTTracker *> {
public:
	TrackerSliders(LayoutContainer *parent, dart::Pose &pose);
	~TrackerSliders();

	void addRow(int i);

	//TypeRecipient<dart::UBCDARTTracker *>
	void processType(dart::UBCDARTTracker *tracker);
	void onStartup();

protected:
	ColumnLayout _cl;
	dart::Pose &_pose;

	vector<SimpleSlider *> _sliders;
};

#endif
