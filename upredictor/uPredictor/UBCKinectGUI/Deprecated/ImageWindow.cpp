#include "ImageWindow.h"
#include "FrameDesc.h"
#include "LayoutContainer.h"

#include <opencv2/opencv.hpp>

bool ImageWindow::_isInitialized = false;

WNDCLASSW ImageWindow::_wc;
map<HWND, ImageWindow *> ImageWindow::_iw;

ImageWindow::ImageWindow(LayoutContainer *parent, FrameDesc &fd,
	wstring name) : _parent(parent), _fd(fd), _x(0), _y(0)
	, _rgb(fd.h, fd.w, CV_8UC3)
{
	if (!_isInitialized)
		initialize(_parent->getHInstance());

	_hwnd = CreateWindowW(_wc.lpszClassName, L"ImageWindow",
		WS_CHILD | WS_VISIBLE,
		_x, _y, getWidth(), getHeight(), _parent->getHWND(), 0,
		_parent->getHInstance(), NULL);
	
	_bi.biSize = sizeof(BITMAPINFOHEADER);
	_bi.biWidth = getWidth();
	_bi.biHeight = getHeight();
	_bi.biPlanes = 1;
	_bi.biBitCount = 24;
	_bi.biCompression = BI_RGB;
	_bi.biSizeImage = getWidth() * getHeight() *3;
	_hbmp = CreateCompatibleBitmap(GetDC(_hwnd), getWidth(), getHeight());

	parent->addChild(this);

	_iw[_hwnd] = this;
}

ImageWindow::~ImageWindow() {}

int ImageWindow::getWidth() {
	return _fd.w;
}

int ImageWindow::getHeight() {
	return _fd.h;
}

void ImageWindow::setOrigin(int x, int y) {
	_x = x;
	_y = y;
}

void ImageWindow::updateSizeAllotment(int w, int h) {

}

HWND ImageWindow::getHWND() {
	return _hwnd;
}

HINSTANCE ImageWindow::getHInstance() {
	return _parent->getHInstance();
}

void ImageWindow::update(cv::Mat &colorImage) {
	cv::cvtColor(colorImage, _rgb, CV_BGRA2BGR);
	cv::flip(_rgb, _rgb, -1);
	InvalidateRect(_hwnd, NULL, FALSE);
	UpdateWindow(_hwnd);
}

void ImageWindow::initialize(HINSTANCE hInstance) {
	_isInitialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"ImageWindow";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	_wc.lpfnWndProc = ImageWindow::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK ImageWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	ImageWindow *iw = _iw[hwnd];
	HDC hdc;

	switch (msg) {
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		HDC memDC = CreateCompatibleDC(hdc);
		SetDIBits(memDC, iw->_hbmp, 0, 1080, iw->_rgb.data, (BITMAPINFO*)&iw->_bi, DIB_RGB_COLORS);
		HANDLE oldbmp = SelectObject(memDC, iw->_hbmp);

		BitBlt(
			hdc,				//_In_ HDC   hdcDest,
			0,					//ps.rcPaint.left,
			0,					//ps.rcPaint.top,
			iw->getWidth(),		//ps.rcPaint.right - ps.rcPaint.left,
			iw->getHeight(),	//ps.rcPaint.bottom - ps.rcPaint.top,
			memDC,//_In_ HDC   hdcSrc,
			0,			//_In_ int   nXSrc,
			0,			//_In_ int   nYSrc,
			SRCCOPY		//_In_ DWORD dwRop
			);
		DeleteDC(memDC);
		//CloseHandle(oldbmp);
		EndPaint(hwnd, &ps);
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}