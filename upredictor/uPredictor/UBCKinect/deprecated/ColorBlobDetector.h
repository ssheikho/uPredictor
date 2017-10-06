#ifndef COLOR_BLOB_DETECTOR_H
#define COLOR_BLOB_DETECTOR_H

#define NOMINMAX

#include "ArrayPt3DCollection.h"
#include "BlobScanner.h"
#include "BoundingBoxScanner.h"
#include "DragRect.h"
#include "ImageChannelProvider.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

//#include <cvblob.h>

#include <vector>

//using namespace std;

class ColorBlobParams;
class SimpleComboBox;

class ColorBlobDetector :
	public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<ImageChannelProvider *>
	, public TypeBroadcaster<cv::Scalar>
	, public TypeBroadcaster<pair<cv::Scalar, cv::Scalar>>
	, public TypeBroadcaster<pair<uint8_t, uint8_t>>
	, public ImageChannelProvider
	, public TypeRecipient<pair<int, int>>
	, public TypeRecipient<DragRect> {
public:

	enum CBDBGR {
		CBD_BGR_R,
		CBD_BGR_G,
		CBD_BGR_B,

		CBD_BGR_MR,
		CBD_BGR_MG,
		CBD_BGR_MB,

		CBD_BGR_MRTB,
		CBD_BGR_MRTG,
		CBD_BGR_MGTB,
		CBD_BGR_MGTR,
		CBD_BGR_MBTR,
		CBD_BGR_MBTG,

		//CBD_BGR_GRADX,
		//CBD_BGR_GRADY,

		CBD_BGR_COUNT
	};

	enum CBDBGRChannels {
		CBD_B = 0,
		CBD_G,
		CBD_R,
		CBD_BGR_CHANNEL_COUNT
	};

	ColorBlobDetector(
		int detectorNumber
		, ColorBlobParams &cbp
		, FrameDesc &yuyFD
		, UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr> &alloc
		, long imageSource
		, long imageChan
		);
	~ColorBlobDetector();

	ColorBlobParams &getCBP();
	BoundingBoxScanner &getBB();

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void TypeRecipient<SimplePool<KinectFrame>::PooledPtr>::onStartup() {}

	//public TypeRecipient<pair<int, int>>
	void processType(std::pair<int, int> t);
	void processType(DragRect t);
	void TypeRecipient<pair<int, int>>::onStartup() {}
	void TypeRecipient<DragRect>::onStartup() {}

	void populateVideoChannelCB(SimpleComboBox *scb);
	void populateBGRChannelCB(SimpleComboBox *scb);

	cv::Mat getImageChannel(size_t source, size_t index);
	cv::Mat getSeg();

protected:
	class MostlyOneColor {
	public:
		MostlyOneColor(FrameDesc &yuyFD);
		~MostlyOneColor();

		void process(
			cv::Mat &a
			, cv::Mat &b, long bMargin
			, cv::Mat &c, long cMargin);

		cv::Mat
			_aMinusB, _aMinusC
			, _aThreshB, _aThreshC
			, _detected;
	};

	void reportColors(SimplePool<KinectFrame>::PooledPtr t, long majorityChan);


	//int _detectorNumber;
	ColorBlobParams &_cbp;
	FrameDesc &_yuyFD;
	long _imageSource, _imageChan;

	BoundingBoxScanner _bb;
	//BlobScanner _bs;

	MostlyOneColor *_mostly[CBD_BGR_CHANNEL_COUNT];

	cv::Mat	_greyOneChan, _segBGR, _blank, &_seg;

	bool _clicked, _dragged;
	std::pair<int, int> _clickLoc;
	DragRect _draggedLoc;

	std::vector<cv::Mat> _bgrSplit;

	cv::Mat *_segmentMats[CBD_BGR_COUNT];
};

#endif