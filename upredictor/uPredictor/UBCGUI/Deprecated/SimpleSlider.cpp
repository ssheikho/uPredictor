#include "SimpleSlider.h"
#include "LayoutContainer.h"
#include "LayoutContainer.h"

#include <CommCtrl.h>

WNDCLASSW SimpleSlider::_wc;
map<HWND, SimpleSlider *> SimpleSlider::_ss;
bool SimpleSlider::_initialized = false;

SimpleSlider::SimpleSlider(LayoutContainer *parent, int w, int h,
	IntValueArray *controlled, int controlledIndex,
	bool deleteControlledIVAAtEnd,
	IntValueArray *listeningTo, int listenIndex) : _parent(parent),
	_w(w), _h(h),
	_controlledIndex(controlledIndex), _listenIndex(listenIndex),
	_curVal(controlled->get(_controlledIndex)),
	_deleteControlledIVAAtEnd(deleteControlledIVAAtEnd),
	_controlled(controlled), _listeningTo(listeningTo) {
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

	int minV = _controlled->getMinVal(_controlledIndex);
	int maxV = _controlled->getMaxVal(_controlledIndex);
	SendMessage(_frameTB, TBM_SETRANGE, (WPARAM)TRUE,
		(LPARAM)MAKELONG(minV, maxV));
	SendMessage(_frameTB, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)_curVal);

	updateFromSrc();
	parent->addChild(this);

	_ss[_hwnd] = this;
	_ss[_frameTB] = this;
}

SimpleSlider::~SimpleSlider() {
	if (_deleteControlledIVAAtEnd) delete _controlled;
	DestroyWindow(_frameTB);
	DestroyWindow(_hwnd);
}

void SimpleSlider::set(int index, int value, void *origin) {
	if (origin != this) {
		void *o = origin == NULL ? this : origin;
		_curVal = value;
		_controlled->set(_controlledIndex, value, o);
		fireUpdate(0, value, o);
	}
}

int SimpleSlider::get(int index) {
	return _curVal;//_controlled->get(_controlledIndex);
}

bool SimpleSlider::hasMin(int index) {
	return _controlled->hasMin(_controlledIndex);
}

bool SimpleSlider::hasMax(int index) {
	return _controlled->hasMax(_controlledIndex);
}

int SimpleSlider::getMinVal(int index) {
	return _controlled->getMinVal(_controlledIndex);
}

int SimpleSlider::getMaxVal(int index) {
	return _controlled->getMaxVal(_controlledIndex);
}

size_t SimpleSlider::getNVals() {
	return 1;
}

void SimpleSlider::updateIVAL(IntValueArray *iva, int index,
	int value, void *origin) {
	if (index == _listenIndex) set(0, value, origin);
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
	int w =
		_controlled->getMaxVal(_controlledIndex) -
		_controlled->getMinVal(_controlledIndex);
	SendMessage(_frameTB, TBM_SETRANGE, (WPARAM)TRUE,
		(LPARAM)MAKELONG(0, w));

	int val = _controlled->get(_controlledIndex);
	SendMessage(_frameTB, TBM_SETPOS, (WPARAM)TRUE, val);
}

void SimpleSlider::updateFromSlider() {
	int pos = SendMessage(_frameTB, TBM_GETPOS, NULL, NULL);
	set(_controlledIndex, pos, NULL);
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