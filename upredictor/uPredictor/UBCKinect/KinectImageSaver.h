#ifndef KINECT_IMAGE_SAVER_H
#define KINECT_IMAGE_SAVER_H

#include <opencv2/opencv.hpp>

#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

#include <iostream>
#include <string>

class KinectImageSaver :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<SimplePool<KinectFrame>::PooledPtr>
{
public:
	KinectImageSaver(string baseFileName);
	~KinectImageSaver();

	void saveNextImage();

	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

	bool hasGoodFrame();
	void resetFound();
	void saveImage();

	bool hasFrame();
	cv::Mat getFrame();

protected:
	string _file;
	bool _saveNextImage;
	int _imagesSaved;

	bool _hasFrame;
	cv::Mat _frame;
	cv::Mat _goodFrame;
	bool _hasGoodFrame;
};

#endif