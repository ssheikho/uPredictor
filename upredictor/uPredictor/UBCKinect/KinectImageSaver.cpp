#include "KinectImageSaver.h"

KinectImageSaver::KinectImageSaver(string baseFileName)
	: _file(baseFileName)
	, _saveNextImage(false)
	, _imagesSaved(0)
	, _hasFrame(false)
	, _hasGoodFrame(false)
{}

KinectImageSaver::~KinectImageSaver() {}

void KinectImageSaver::saveNextImage()
{
	_saveNextImage = true;
}

void KinectImageSaver::processType(SimplePool<KinectFrame>::PooledPtr t)
{
	// For HIGHGUI window construction.
	_hasFrame = true;
	// cvtColor(t->_rgb, _frame, CV_RGB2BGR);
	_frame = t->_depthBGRA;
	
/*	vector<cv::Point2f> corners;
	bool found = cv::findChessboardCorners(_frame, cv::Size(7, 9), corners,
			cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

	if (found)
	{
		_hasGoodFrame = found;
		_goodFrame = _frame;
		cout << "FOUND GOOD FRAME" << endl;
	}*/

	// Important part of the function.
	if (_saveNextImage)
	{
		string fileName = _file + to_string(_imagesSaved) + ".jpg";
		imwrite("imagefolder/" + fileName, _frame);
		cout << "Saved " << fileName << endl;
		_imagesSaved++;
		_saveNextImage = false;
	}
	fireUpdate(t);
}

void KinectImageSaver::onStartup() {}

// These functions were used when trying to have frames automatically
// saved when corners were detected on both cameras at the same time.
// The resulting set of images did not produce good homography output.
bool KinectImageSaver::hasGoodFrame()
{
	if (_hasGoodFrame)
		cout << "GOOD FRAME " << _file << endl;
	return _hasGoodFrame;
}

void KinectImageSaver::resetFound()
{
	_hasGoodFrame = false;
}

void KinectImageSaver::saveImage()
{
		string fileName = _file + to_string(_imagesSaved) + ".jpg";
		imwrite("imagefolder/" + fileName, _goodFrame);
		cout << "Saved " << fileName << endl;
		_imagesSaved++;
		// _saveNextImage = false;
		_hasGoodFrame = false;
}

// These functions are only here for constructing a HIGHGUI window
// that's required for the waitKey function to work.
bool KinectImageSaver::hasFrame()
{
	return _hasFrame;
}

cv::Mat KinectImageSaver::getFrame()
{
	return _frame;
}