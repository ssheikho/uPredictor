#include "UBCUtil.h"
#include "VideoPlayer.h"

VideoPlayer::VideoPlayer(wstring fileName)
{
	_vc.open(wstringToString(fileName));
	_frameCount = _vc.get(CV_CAP_PROP_FRAME_COUNT);
	_w = _vc.get(CV_CAP_PROP_FRAME_WIDTH);
	_h = _vc.get(CV_CAP_PROP_FRAME_HEIGHT);
}

VideoPlayer::~VideoPlayer() {}

void VideoPlayer::processType(long t)
{
	cv::Mat frame;
	_vc.set(CV_CAP_PROP_POS_FRAMES, t);
	_vc.read(frame);
	fireUpdate(frame);
}

void VideoPlayer::onStartup() {};