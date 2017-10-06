#include "SimpleSlider.h"
#include "LayoutContainer.h"

#include <CommCtrl.h>

WNDCLASSW SimpleSlider::_wc;
map<HWND, SimpleSlider *> SimpleSlider::_ss;
bool SimpleSlider::_initialized = false;

SimpleSlider::SimpleSlider(
	LayoutContainer *parent
	, int w
	, int h
	, long minVal
	, long maxVal
	, long startVal
	, double scaleVal) :
	_parent(parent)
	, _w(w), _h(h)
	, _minVal(minVal)
	, _maxVal(maxVal)
	, _curVal(startVal)
	, _scaleVal(scaleVal)
{
	if (!_initialized) initialize(parent->getHInstance());

	_hwnd = CreateWindowW(_wc.lpszClassName, L"SimpleSlider",
		//WS_CHILD | WS_VISIBLE,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		0, 0, _w, _h,
		_parent->getHWND(), 0,
		_parent->getHInstance(), NULL);

	_frameTB = CreateWindow(TRACKBAR_CLASS, TEXT("Trackbar Control"),
		WS_CHILD | WS_VISIBLE,
		0, 0, _w, _h,
		_hwnd, NULL,
		parent->getHInstance(), NULL);

	SendMessage(_frameTB, TBM_SETPAGESIZE, 0, (LPARAM)1); // new page size

	SendMessage(_frameTB, TBM_SETRANGE, (WPARAM)TRUE,
		(LPARAM)MAKELONG(_minVal, _maxVal));
	SendMessage(_frameTB, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)_curVal);

	updateFromSrc();
	parent->addChild(this);

	_ss[_hwnd] = this;
	_ss[_frameTB] = this;
}

SimpleSlider::~SimpleSlider() {
	DestroyWindow(_frameTB);
	DestroyWindow(_hwnd);
}

void SimpleSlider::processType(long t) {
	_curVal = t;
	TypeBroadcaster<long>::fireUpdate(_curVal);
	TypeBroadcaster<double>::fireUpdate((double)_curVal/_scaleVal);
}

void SimpleSlider::processType(double t) {
	_curVal = t * _scaleVal;
	TypeBroadcaster<long>::fireUpdate(_curVal);
	TypeBroadcaster<double>::fireUpdate(t);
}

void SimpleSlider::set(long val) {
	_curVal = val;
	updateFromSrc();
	TypeBroadcaster<long>::fireUpdate(_curVal);
	TypeBroadcaster<double>::fireUpdate((double)_curVal / _scaleVal);
}

long SimpleSlider::get() {
	return _curVal;
}

long SimpleSlider::getMin() {
	return _minVal;
}

long SimpleSlider::getMax() {
	return _maxVal;
}

int SimpleSlider::getWidth() {
	return _w;
}

int SimpleSlider::getHeight() {
	return _h;
}

void SimpleSlider::setOrigin(int x, int y) {
	MoveWindow(_hwnd, x, y, getWidth(), getHeight(), TRUE);
	MoveWindow(_frameTB, 0, 0, getWidth(), getHeight(), TRUE);
}

void SimpleSlider::updateSizeAllotment(int w, int h) {
	if(w != -1) _w = w;
	if(h != -1) _h = h;
}

HWND SimpleSlider::getHWND() {
	return _hwnd;
}

HINSTANCE SimpleSlider::getHInstance() {
	return _parent->getHInstance();
}

void SimpleSlider::updateFromSrc() {
	//int w =
	//	_controlled->getMaxVal(_controlledIndex) -
	//	_controlled->getMinVal(_controlledIndex);
	//SendMessage(_frameTB, TBM_SETRANGE, (WPARAM)TRUE,
	//	(LPARAM)MAKELONG(0, w));

	SendMessage(_frameTB, TBM_SETPOS, (WPARAM)TRUE, _curVal);
}

void SimpleSlider::updateFromSlider() {
	_curVal = SendMessage(_frameTB, TBM_GETPOS, NULL, NULL);
	TypeBroadcaster<long>::fireUpdate(_curVal);
	TypeBroadcaster<double>::fireUpdate((double)_curVal / _scaleVal);
}

void SimpleSlider::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"SimpleSlider";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = SimpleSlider::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK SimpleSlider::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	map<HWND, SimpleSlider *>::iterator iter = _ss.find(hwnd);
	if (iter != _ss.end()) {
		SimpleSlider *ss = iter->second;
		if (ss) {
			switch (msg) {
			case WM_PAINT:
				ss->updateFromSrc();
				//ss->updateThumbFromRec();
				break;

			case WM_HSCROLL:
				ss->updateFromSlider();
				break;
			}
		}
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}