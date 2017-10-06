#ifndef CUDA_COLOR_TRACKER_GUI_H
#define CUDA_COLOR_TRACKER_GUI_H

#include "ColumnLayout.h"
#include "ExternalValueListener.h"
#include "LayoutElement.h"
#include "RowLayout.h"
#include "SimpleComboBox.h"
#include "SimpleLabeledSlider.h"
#include "TrackerCUDAStructs.h"
#include "UBCEntry.h"

class CUDAColorTrackerGUI : public LayoutElement {
public:
	CUDAColorTrackerGUI(
		LayoutContainer *parent
		, struct MarginalTrackerParams *mtp);
	~CUDAColorTrackerGUI();
	
	// LayoutElement
	GtkWidget *getWidget();

protected:
	void initializeBGRComboBox(SimpleComboBox* scb);

	ExternalValueListener<long> _trackedChanEVL, _chanAEVL, _chanBEVL,
								_marginAEVL, _marginBEVL,
								_renderColorREVL, _renderColorGEVL, _renderColorBEVL;

	// GUI consists of multiple rows within a single column.
	ColumnLayout _cl;
	RowLayout _rowTracked, _rowA, _rowB;

	UBCEntry _chanTrackedL, _chanAL, _chanBL;
	SimpleComboBox _chanTrackedCB, _chanACB, _chanBCB;
	SimpleLabeledSlider _chanAS, _chanBS;

	UBCEntry _emptyTrackedL, _emptyAL, _emptyBL;

	UBCEntry _renderColorRL, _renderColorGL, _renderColorBL;
	SimpleLabeledSlider _renderColorR, _renderColorG, _renderColorB;
};

#endif
