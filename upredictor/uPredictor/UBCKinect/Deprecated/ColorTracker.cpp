#include "ColorTracker.h"
#include "ColorBlobDetector.h"
#include "ColorBlobParams.h"
#include "UBCUtil.h"

ColorTracker::ColorTracker(
	FrameDesc &yuyFD
	, UBC::Allocator<SimplePool<BoxAndConstellation>::PooledPtr> &ptCollAlloc
	, long imageSource
	, long imageChan
	, UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc) :
	_ii(this)
	, _yuyFD(yuyFD)
	, _ptCollAlloc(ptCollAlloc)
	, _imageSource(imageSource)
	, _imageChan(imageChan)
	, _icb(0, 0)
	, _t(alloc.getInstance()){
	_tbcs.addChannel(this);
	_tbcs.addRecipient(&_icb);
}

ColorTracker::~ColorTracker() {}

TypeRecipient<pair<int, int>> &ColorTracker::getTRIntInt() {
	return _trcs;
}

TypeRecipient<DragRect> &ColorTracker::getTRDragRect() {
	return _trdr;
}

TypeBroadcasterChannelSelector<ImageChannelProvider *>
&ColorTracker::getTBCS() {
	return _tbcs;
}

ImageChannelBroadcaster &ColorTracker::getICB() {
	return _icb;
}

ColorBlobDetector *ColorTracker::add(wstring name) {
	return add(name, new ColorBlobParams(_ii, name));
}

ColorBlobDetector *ColorTracker::add(wstring name, ColorBlobParams *cbp) {
	_bp[name] = cbp;
	ColorBlobDetector *cbd = _bd[name] =
		new ColorBlobDetector(
			_bd.size(), *cbp, _yuyFD, _ptCollAlloc, _imageSource, _imageChan);
	_tbcs.addChannel(cbd);
	_trcs.add(cbd);
	_trdr.add(cbd);
	return cbd;
}

void ColorTracker::load(wstring filename) {
	fstream f;
	f.open(filename, ios::in | ios::binary);

	long nBlobTypes = _bd.size();
	f.write((char *)&nBlobTypes, sizeof(long));

	for (
		map<wstring, ColorBlobDetector *>::iterator iter = _bd.begin();
		iter != _bd.end();
		iter++) {
		saveWString(f, iter->first);
		iter->second->getCBP().save(f);
	}
}

void ColorTracker::save(wstring filename) {
	fstream f;
	f.open(filename, ios::out | ios::binary | ios::trunc);

	long nBlobTypes;
	f.read((char *)&nBlobTypes, sizeof(long));

	for (int i = 0; i < nBlobTypes; i++) {
		wstring name = readWString(f);
		ColorBlobParams *cbp = new ColorBlobParams(_ii, name);
		cbp->load(f);
		add(name, cbp);
		//_bp[name] = cbp;
	}

}

void ColorTracker::processType(SimplePool<KinectFrame>::PooledPtr t) {
	_t = t;

	t->_pts.getBGRImage().copyTo(t->_depthSegImg);
	for (map<wstring, ColorBlobDetector *>::iterator iter = _bd.begin();
	iter != _bd.end(); iter++) {
		ColorBlobDetector *cbd = iter->second;
		ColorBlobParams &cbp = cbd->getCBP();
		cbd->processType(t);
		t->_depthSegImg.setTo(
			cv::Scalar(cbp._drawB._t, cbp._drawG._t, cbp._drawR._t)
			, cbd->getSeg());
	}

	fireUpdate(this);
}

void ColorTracker::onStartup() {}

cv::Mat ColorTracker::getImageChannel(size_t source, size_t index) {
	return _t->_depthSegImg;
}

void ColorTracker::rename(wstring from, wstring to) {
	map<wstring, ColorBlobParams *>::iterator iterA = _bp.find(from);
	map<wstring, ColorBlobDetector *>::iterator iterB = _bd.find(from);
	_bp[to] = iterA->second;
	_bd[to] = iterB->second;
	_bp.erase(iterA);
	_bd.erase(iterB);
}

ColorTracker::TRDBManager::TRDBManager(ColorTracker *ct) : _ct(ct) {}
ColorTracker::TRDBManager::~TRDBManager() {}

void ColorTracker::TRDBManager::rename(wstring from, wstring to) {
	_ct->rename(from, to);
}