#ifndef COLOR_ROW_H
#define COLOR_ROW_H

#include "RowLayout.h"
#include "UBCEntry.h"

#include <opencv/cv.h>

class ColorRow :
public LayoutElement
, public TypeRecipient<cv::Scalar> {
public:
	ColorRow(
		LayoutContainer *parent
		);
	~ColorRow();

	//LayoutElement
	GtkWidget *getWidget();

	//TypeRecipient<cv::Scalar>
	void processType(cv::Scalar t);
	void onStartup();

protected:
	RowLayout _rlColor;
	UBCEntry _bL, _bE, _gL, _gE, _rL, _rE;
};

#endif
