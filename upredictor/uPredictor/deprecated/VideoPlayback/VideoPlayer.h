#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include "TypeRecipient.h"
#include "TypeBroadcaster.h"

#include <opencv2/opencv.hpp>

class VideoPlayer : public TypeRecipient<long>
	, public TypeBroadcaster<cv::Mat>
{
public:
	double _frameCount, _w, _h;

	VideoPlayer(wstring fileName);
	~VideoPlayer();

	// TypeRecipient
	void processType(long t);
	void onStartup();

	// TypeBroadcaster
	void addRecipient(TypeRecipient<cv::Mat> * or ) {
		_or.push_back(or );
	}

protected:
	cv::VideoCapture _vc;
};

#endif