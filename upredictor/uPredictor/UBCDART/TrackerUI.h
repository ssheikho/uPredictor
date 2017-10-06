#ifndef TRACKER_UI_H
#define TRACKER_UI_H

#include "ColumnLayout.h"
#include "UBCDARTTracker.h"

#include "pose/pose.h"

#include <vector>

using namespace std;

class UBCEntry;

class TrackerUI :
	public TypeRecipient<dart::UBCDARTTracker *> {
public:
	TrackerUI(LayoutContainer *parent, dart::Pose &pose, int modelNo);
	~TrackerUI();

	void processType(dart::UBCDARTTracker *tracker);
	void onStartup();

protected:
	void addRow(int i);

	int _modelNo;
	ColumnLayout _cl;
	vector<UBCEntry *> _entries;
};

#endif
