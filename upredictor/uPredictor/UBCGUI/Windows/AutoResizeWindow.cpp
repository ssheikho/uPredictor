#include "AutoResizeWindow.h"

WNDCLASSW AutoResizeWindow::_wc;
map<HWND, AutoResizeWindow *> AutoResizeWindow::_hcb;
bool AutoResizeWindow::_initialized = false;

AutoResizeWindow::AutoResizeWindow(HINSTANCE hInstance, int minW, int minH) :
_hInstance(hInstance), _minW(minW), _minH(minH), _curW(_minW), _curH(_minH) {
	if (!_initialized) initialize(hInstance);

	_hwnd = CreateWindowW(_wc.lpszClassName, L"AutoResizeWindow",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, minW, minH, 0, 0, _hInstance, NULL);

	_hcb[_hwnd] = this;

	startup();
}

AutoResizeWindow::~AutoResizeWindow() {
	DestroyWindow(_hwnd);
}

int AutoResizeWindow::getWidth() {
	return _curW;
}

int AutoResizeWindow::getHeight() {
	return _curH;
}

void AutoResizeWindow::setOrigin(int x, int y) {
	MoveWindow(_hwnd, x, y, _curW, _curH, TRUE);
}

void AutoResizeWindow::prepareForSizeChanges() {}

void AutoResizeWindow::postSizeChanges() {}

void AutoResizeWindow::updateSizeAllotment(int w, int h) {}

HWND AutoResizeWindow::getHWND() {
	return _hwnd;
}

HINSTANCE AutoResizeWindow::getHInstance() {
	return _hInstance;
}

int AutoResizeWindow::getMaxWidth(LayoutElement *child) {
	return -1;
}

int AutoResizeWindow::getMaxHeight(LayoutElement *child) {
	return -1;
}

void AutoResizeWindow::updateSizeInfo(LayoutElement *child) {
	int w = child->getWidth() + 16;		//Size of border
	int h = child->getHeight() + 40;	//Size of border
	if (w > _curW) _curW = w;
	if (h > _curH) _curH = h;

	RECT r;
	GetWindowRect(_hwnd, &r);
	MoveWindow(_hwnd, r.left, r.top, _curW, _curH, TRUE);
}

void AutoResizeWindow::onChildAdd(LayoutElement *child) {
	updateSizeInfo(child);
}

void AutoResizeWindow::onClear() {}

void AutoResizeWindow::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"AutoResizeWindow";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = AutoResizeWindow::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK AutoResizeWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		_hcb[hwnd]->shutdown();
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void AutoResizeWindow::onStartup() {}

void AutoResizeWindow::onShutdown() {
	DestroyWindow(_hwnd);
	PostQuitMessage(0);
}

void AutoResizeWindow::onAddChained(ShutdownInterface *si) {}
