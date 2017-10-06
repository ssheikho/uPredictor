#ifndef VIDEO_RESCALER_H
#define VIDEO_RESCALER_H

#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <opencv/cv.hpp>

class VideoRescaler :
	public TypeBroadcaster<cv::Mat>
	, public TypeRecipient<cv::Mat> {
public:
	VideoRescaler(int destW, int destH);
	~VideoRescaler();

	void processType(const cv::Mat t);

protected:
	cv::Mat _out;
};

#endif
