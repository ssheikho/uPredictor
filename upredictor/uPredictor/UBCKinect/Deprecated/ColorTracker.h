#ifndef COLOR_TRACKER_H
#define COLOR_TRACKER_H

#include "Allocator.h"
#include "ArrayPt3DCollection.h"
#include "BoxAndConstellation.h"
#include "DragRect.h"
#include "FrameDesc.h"
#include "ImageChannelBroadcaster.h"
#include "ImageChannelProvider.h"
#include "IndexInterface.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeBroadcasterChannelSelector.h"
#include "TypeRecipient.h"
#include "TypeRecipientChannelSelector.h"

#include <map>
#include <queue>

using namespace std;

class ColorBlobDetector;
class ColorBlobParams;

class ColorTracker :
public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
, public TypeBroadcaster<ImageChannelProvider *>
, public ImageChannelProvider
{
public:
	ColorTracker(
		FrameDesc &yuyFD
		, UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr>
		&ptCollAlloc
		, long imageSource
		, long imageChan
		, UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc);
	~ColorTracker();

	TypeRecipient<pair<int, int>> &getTRIntInt();
	TypeRecipient<DragRect> &getTRDragRect();
	TypeBroadcasterChannelSelector<ImageChannelProvider *> &getTBCS();
	ImageChannelBroadcaster &getICB();

	ColorBlobDetector *add(wstring name);

	//public SimpleLoadSave
	void load(wstring filename);
	void save(wstring filename);

	//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	void processType(SimplePool<KinectFrame>::PooledPtr t);
	void onStartup();

	//public ImageChannelProvider
	cv::Mat getImageChannel(size_t source, size_t index);

protected:
	class TRDBManager : public IndexInterface<wstring> {
	public:
		TRDBManager(ColorTracker *ct);
		~TRDBManager();

		void rename(wstring from, wstring to);

	protected:
		ColorTracker *_ct;
	};

	ColorBlobDetector *add(wstring name, ColorBlobParams *cbp);

	void rename(wstring from, wstring to);

	TRDBManager _ii;
	FrameDesc &_yuyFD;
	UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr> &_ptCollAlloc;
	long _imageSource, _imageChan;

	TypeRecipientChannelSelector<pair<int, int>> _trcs;
	TypeRecipientChannelSelector<DragRect> _trdr;

	TypeBroadcasterChannelSelector<ImageChannelProvider *> _tbcs;
	ImageChannelBroadcaster _icb;

	map<wstring, ColorBlobParams *> _bp;
	map<wstring, ColorBlobDetector *> _bd;

	SimplePool<KinectFrame>::PooledPtr _t;
};

#endif