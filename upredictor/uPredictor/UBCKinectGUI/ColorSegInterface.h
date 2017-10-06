#ifndef COLOR_SEG_INTERFACE_H
#define COLOR_SEG_INTERFACE_H

#include "ColorRow.h"
#include "ColumnLayout.h"
#include "GridLayout.h"
#include "ImageChannelBroadcaster.h"
#include "IntSwitch.h"
#include "RowLayout.h"
#include "SimpleLabeledComboBox.h"
#include "SimpleLabeledSlider.h"
#include "UBCButton.h"
#include "UBCEntry.h"

#include <opencv\cv.h>

class ColorBlobDetector;
class ColorBlobParams;

class ColorSegInterface :
	public LayoutElement
	, public TypeRecipient<cv::Scalar>
	, public TypeRecipient<pair<cv::Scalar, cv::Scalar>>
	, public TypeRecipient<pair<uint8_t, uint8_t>>
	, public IntSwitch
{
public:
	enum CSIClickState {
		CSI_FREE_CLICK,
		CSI_RECT_FIRST,
		CSI_RECT_SECOND
	};

	ColorSegInterface(
		LayoutContainer *parent
		, ColorBlobDetector *cbd
		);
	~ColorSegInterface();

	ImageChannelBroadcaster &getICB();

	//LayoutElement
	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	//public TypeRecipient<cv::Scalar>
	void processType(cv::Scalar t);
	void TypeRecipient<cv::Scalar>::onStartup() {}

	//public TypeRecipient<pair<cv::Scalar, cv::Scalar>>
	void processType(pair<cv::Scalar, cv::Scalar> t);
	void TypeRecipient<pair<cv::Scalar, cv::Scalar>>::onStartup() {}

	//public TypeRecipient<pair<uint8_t, uint8_t>>
	void processType(pair<uint8_t, uint8_t> t);
	void TypeRecipient<pair<uint8_t, uint8_t>>::onStartup() {}

	//public IntSwitch
	void updateSwitch(int val);

protected:
	ColumnLayout _cl;
	RowLayout _nameRL;
	UBCEntry _nameL, _nameE;
	GridLayout _glColors;
	UBCEntry *_colCur, *_colMin, *_colMax
		, *_minMargL, *_minMargE, *_maxMargL, *_maxMargE;
	ColorRow *_crCur, *_crMin, *_crMax;
	SimpleLabeledComboBox _scbMajorityChannel;
	GridLayout _gl;

	UBCEntry
		 *_bMinusGL, *_bMinusRL
		, *_gMinusBL, *_gMinusRL
		, *_rMinusBL, *_rMinusGL
		
		, *_minPtsL

		, *_drawBL, *_drawGL, *_drawRL

		//, *_gradientL
		;

	SimpleLabeledSlider
		 *_bMinusGThresh, *_bMinusRThresh
		, *_gMinusBThresh, *_gMinusRThresh
		, *_rMinusBThresh, *_rMinusGThresh

		, *_minPtsThresh

		, *_drawB, *_drawG, *_drawR

		//, *_gradientThresh
		;

	ImageChannelBroadcaster _icb;
};

#endif