#ifndef IMAGE_CHANNEL_PROVIDER_H
#define IMAGE_CHANNEL_PROVIDER_H

#include <opencv/cv.hpp>

class ImageChannelProvider {
public:
	virtual cv::Mat &getImageChannel(size_t source, size_t index) = 0;
};

#endif
