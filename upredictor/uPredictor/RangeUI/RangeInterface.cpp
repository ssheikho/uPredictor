#include"RangeInterface.h"

RangeInterface::RangeInterface(
	LayoutContainer *parent
	, UBC::Allocator<SimplePool<KinectFrame>::PooledPtr> &alloc
	) :
	_coords(0.0,0.0)
	, _cl(parent, 25, 25)
	, _rl(&_cl, 25, 25)
	, _xL(L"X: ", &_rl, false, 25, 25)
	, _xE(L"0", &_rl, true, 50, 25)
	, _yL(L"Y: ", &_rl, false, 25, 25)
	, _yE(L"0", &_rl, true, 50, 25)
	, _zL(L"Z: ", &_rl, false, 25, 25)
	, _zE(L"0", &_rl, true, 50, 25)
{
	//_xE.setTextD(iw._clickEnd.first)

}

RangeInterface::~RangeInterface() {}

int RangeInterface::getWidth() {
	return _rl.getWidth();
}

int RangeInterface::getHeight() {
	return _rl.getHeight();
}

void RangeInterface::setOrigin(int x, int y) {
	return _rl.setOrigin(x, y);
}

void RangeInterface::updateSizeAllotment(int w, int h) {
	return _rl.updateSizeAllotment(w, h);
}

HWND RangeInterface::getHWND() {
	return _rl.getHWND();
}

HINSTANCE RangeInterface::getHInstance() {
	return _rl.getHInstance();
}

pair<int, int> RangeInterface::getCoords() {
	return _coords;
}


void RangeInterface::processType(pair<int, int> t)
{
	_coords = t;

	_xE.setTextI(_coords.first);
	_yE.setTextI(_coords.second);
}

//public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
//void processType(SimplePool<KinectFrame>::PooledPtr t) {
	
//}

