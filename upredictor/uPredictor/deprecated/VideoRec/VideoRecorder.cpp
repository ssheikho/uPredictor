#include "VideoRecorder.h"
#include "UBCUtil.h"

VideoRecorder::VideoRecorder(wstring fileName, FrameDesc &fd)
{
	int fourcc = -1;
	_vw.open(wstringToString(fileName), fourcc, 30, cvSize(fd.w, fd.h), true);
}

VideoRecorder::~VideoRecorder() {}

cv::VideoWriter VideoRecorder::getVideoWriter() {
	return _vw;
}

void VideoRecorder::processType(cv::Mat t) {
	_vw.write(t);
}

void VideoRecorder::onStartup() {}