#include "ScrollingWindow.h"

bool ScrollingWindow::_initialized = false;
WNDCLASSW ScrollingWindow::_wc;
WNDCLASSW ScrollingWindow::_wcScroll;
map<HWND, ScrollingWindow *> ScrollingWindow::_sw;

ScrollingWindow::ScrollingWindow(LayoutContainer *parent, int w, int h) :
_parent(parent), _x(0), _y(0), _w(w), _h(h), _vScroll(0), _antiFlash(false) {
	if (!_initialized) initialize(_parent->getHInstance());
	_hwnd = CreateWindowW(_wc.lpszClassName, L"ScrollingWindow",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		0, 0,
		_w, _h,
		_parent->getHWND(), 0,
		_parent->getHInstance(), NULL);

	_hScroll = CreateWindowEx(0,
		_wcScroll.lpszClassName, L"HandoverAnnotationTableScroll",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL,
		0, 0,
		_w - GetSystemMetrics(SM_CXVSCROLL), _h,
		_hwnd, 0, _parent->getHInstance(), NULL);

	_si.nMin = 0;
	_si.nPos = 0;
	_si.cbSize = sizeof(SCROLLINFO);
	_si.fMask = SIF_POS | SIF_RANGE;
	updateScrollbarHeight();

	_sw[_hwnd] = this;
	_sw[_hScroll] = this;

	_parent->addChild(this);
}

ScrollingWindow::~ScrollingWindow() {}

int ScrollingWindow::getWidth() {
	return _w;
}

int ScrollingWindow::getHeight() {
	return _h;
}

void ScrollingWindow::setOrigin(int x, int y) {
	MoveWindow(_hwnd, _x = x, _y = y, _w, _h, TRUE);
}

void ScrollingWindow::updateSizeAllotment(int w, int h) {
	MoveWindow(_hwnd, _x, _y, _w = w, _h = h, TRUE);
}

HWND ScrollingWindow::getHWND() {
	return _hScroll;
}

HINSTANCE ScrollingWindow::getHInstance() {
	return _parent->getHInstance();
}

int ScrollingWindow::getMaxWidth(LayoutElement *child) {
	return -1;
}

int ScrollingWindow::getMaxHeight(LayoutElement *child) {
	return -1;
}

void ScrollingWindow::prepareForSizeChanges() {
	_spareScroll = _vScroll;
	_antiFlash = true;
	/*
	ScrollWindowEx(
		_hScroll,
		0,
		-_vScroll,
		NULL,
		NULL,
		0, 0, SW_INVALIDATE | SW_SCROLLCHILDREN | SW_ERASE
		);
	*/
	//updateScrollbarPosInner(0, 0);
}

void ScrollingWindow::postSizeChanges() {
	ScrollWindowEx(
		_hScroll,
		0,
		_spareScroll,
		NULL,
		NULL,
		0, 0, SW_INVALIDATE | SW_SCROLLCHILDREN | SW_ERASE
		);
	_antiFlash = false;
}

void ScrollingWindow::updateSizeInfo(LayoutElement *child) {
	updateScrollbarHeight();
}


void ScrollingWindow::initialize(HINSTANCE hInstance) {
	_wc = { 0 };
	_wc.lpszClassName = L"ScrollingWindow";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = ScrollingWindow::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	_wcScroll = { 0 };
	_wcScroll.lpszClassName = L"ScrollingWindowScroll";
	_wcScroll.hInstance = hInstance;
	_wcScroll.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	_wcScroll.lpfnWndProc = ScrollingWindow::WndProc;
	_wcScroll.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
	RegisterClassW(&_wcScroll);
}

LRESULT CALLBACK ScrollingWindow::WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {
		//case WM_SIZE:
		//	MoveWindow(_hwnd, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		//	break;

	case WM_VSCROLL:
	{
		int sbPos;
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
		case SB_PAGEUP:
			_sw[hwnd]->updateScrollbarLineUp();
			break;

		case SB_LINEDOWN:
		case SB_PAGEDOWN:
			_sw[hwnd]->updateScrollbarLineDown();
			break;

		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			// get the new position from message parameter
			sbPos = HIWORD(wParam);
			//sbPos = GetScrollPos(_atc[hwnd]->_hScroll, SB_CTL);
			_sw[hwnd]->updateScrollbarPos(sbPos);
			//abort();
			break;
		}

	}
	break;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void ScrollingWindow::onChildAdd(LayoutElement *child) {
	//updateScrollbarHeight();
}

void ScrollingWindow::onClear() {
	updateScrollbarHeight();
}

void ScrollingWindow::updateScrollbarHeight() {
	//updateScrollbarPosInner(0, 0);
	int height = 0;
	if(_child.size()) height = _child[_child.size() - 1]->getHeight();
	_si.nMax = height > _h ? height : _h;
	SetScrollInfo(_hScroll, SB_VERT, &_si, TRUE);

	/*
	ScrollWindowEx(
		_hScroll,
		0,
		_spareScroll,
		NULL,
		NULL,
		0, 0, SW_INVALIDATE | SW_SCROLLCHILDREN | SW_ERASE
		);
	*/
	//UpdateWindow(_hScroll);
	//updateScrollbarPosInner(_lastPos, _lastVScroll);
}

void ScrollingWindow::updateScrollbarPos(int pos) {
	if (!_antiFlash) {
		int dy = _si.nPos - pos;
		_vScroll += dy;
		_si.nPos = pos;
		SetScrollInfo(_hScroll, SB_VERT, &_si, TRUE);

		ScrollWindowEx(
			_hScroll,
			0,
			dy,
			NULL,
			NULL,
			0, 0, SW_INVALIDATE | SW_SCROLLCHILDREN | SW_ERASE
			);
		UpdateWindow(_hScroll);
	}
}

void ScrollingWindow::updateScrollbarLineUp() {
	updateScrollbarPos(_si.nPos - 25);
}

void ScrollingWindow::updateScrollbarLineDown() {
	updateScrollbarPos(_si.nPos + 25);
}