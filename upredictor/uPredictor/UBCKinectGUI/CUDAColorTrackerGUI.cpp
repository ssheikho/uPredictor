#include "CUDAColorTrackerGUI.h"

CUDAColorTrackerGUI::CUDAColorTrackerGUI(
	LayoutContainer *parent
	, struct MarginalTrackerParams *mtp) :
	_trackedChanEVL(&mtp->_mostlyChan)
	, _chanAEVL(&mtp->_fromChanA)
	, _chanBEVL(&mtp->_fromChanB)
	, _marginAEVL(&mtp->_marginA)
	, _marginBEVL(&mtp->_marginB)

	, _renderColorREVL(&mtp->_indicColorR)
	, _renderColorGEVL(&mtp->_indicColorG)
	, _renderColorBEVL(&mtp->_indicColorB)

	, _cl(parent, 900, 145)

	, _rowTracked(&_cl, 900, 50)
	, _rowA(&_cl, 900, 50)
	, _rowB(&_cl, 900, 50)

	, _chanTrackedL("Tracked Chan:", &_rowTracked, false, 100, 50)
	, _chanAL("Chan A:", &_rowA, false, 100, 50)
	, _chanBL("Chan B:", &_rowB, false, 100, 50)

	, _chanTrackedCB(&_rowTracked)
	, _chanACB(&_rowA)
	, _chanBCB(&_rowB)

	, _chanAS(&_rowA, 0, 255, 127, 0)
	, _chanBS(&_rowB, 0, 255, 127, 0)

	, _emptyTrackedL("", &_rowTracked, false, 300, 50)
	, _emptyAL("", &_rowA, false, 50, 50)
	, _emptyBL("", &_rowB, false, 50, 50)

	, _renderColorRL("Render Color R:", &_rowTracked, false, 150, 50)
	, _renderColorGL("Render Color G:", &_rowA, false, 150, 50)
	, _renderColorBL("Render Color B:", &_rowB, false, 150, 50)

	, _renderColorR(&_rowTracked, 0, 255, 127, 0)
	, _renderColorG(&_rowA, 0, 255, 127, 0)
	, _renderColorB(&_rowB, 0, 255, 127, 0) {

	initializeBGRComboBox(&_chanTrackedCB);
	initializeBGRComboBox(&_chanACB);
	initializeBGRComboBox(&_chanBCB);

	_chanTrackedCB.setSelectedValue(mtp->_mostlyChan);
	_chanACB.setSelectedValue(mtp->_fromChanA);
	_chanBCB.setSelectedValue(mtp->_fromChanB);

	_chanTrackedCB.addRecipient(&_trackedChanEVL);
	_chanACB.addRecipient(&_chanAEVL);
	_chanBCB.addRecipient(&_chanBEVL);

	_chanAS.getSS().TypeBroadcaster<long>::addRecipient(&_marginAEVL);
	_chanBS.getSS().TypeBroadcaster<long>::addRecipient(&_marginBEVL);

	_renderColorR.getSS().TypeBroadcaster<long>::addRecipient(&_renderColorREVL);
	_renderColorG.getSS().TypeBroadcaster<long>::addRecipient(&_renderColorGEVL);
	_renderColorB.getSS().TypeBroadcaster<long>::addRecipient(&_renderColorBEVL);
}

CUDAColorTrackerGUI::~CUDAColorTrackerGUI() {
	_cl.~ColumnLayout();
}

GtkWidget *CUDAColorTrackerGUI::getWidget() {
	return _cl.getWidget();
}

void CUDAColorTrackerGUI::initializeBGRComboBox(SimpleComboBox* scb) {
	scb->addSelection("B", 0);
	scb->addSelection("G", 1);
	scb->addSelection("R", 2);
}
