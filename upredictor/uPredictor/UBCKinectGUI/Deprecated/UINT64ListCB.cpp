#include "UINT64ListCB.h"
#include "LayoutContainer.h"
#include "UBCUtil.h"
#include "UINT64List.h"
#include "UINT64Value.h"

#include <CommCtrl.h>

#include <codecvt>

WNDCLASSW UINT64ListCB::_wc;
map<HWND, UINT64ListCB *> UINT64ListCB::_aeui;
bool UINT64ListCB::_initialized = false;

UINT64ListCB::UINT64ListCB(
	UINT64List *aet, UINT64Value *val,
	LayoutContainer *parent,
	int minW, int minH) : 
	_aet(aet), _val(val),
	_parent(parent),
	_x(0), _y(0),
	_minW(minW), _minH(minH),
	_w(minW), _h(minH) {
	if (!_initialized) initialize(_parent->getHInstance());

	_hwnd = CreateWindowW(_wc.lpszClassName, L"AnnotationEnumUI",
		WS_CHILD | WS_VISIBLE,
		0, 0, _minW, _minH, _parent->getHWND(), 0,
		_parent->getHInstance(), NULL);
	_hWndCB = CreateWindow(WC_COMBOBOX, TEXT(""),
		CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED |
		WS_VISIBLE,
		0, 0, _minW, _minH * 3, _hwnd, NULL, _parent->getHInstance(),
		NULL);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	for (int i = 0; i < aet->nUINT64s(); i++) {
		UINT64 value = aet->getUINT64(i);
		
		SendMessage(_hWndCB,
			(UINT)CB_INSERTSTRING, (WPARAM)-1,
			(LPARAM)intToWString(value).c_str());
	}

	updateFromValue();
	//updateCurSelFromHand();

	parent->addChild(this);

	_aeui[_hwnd] = this;
	_aeui[_hWndCB] = this;
}

UINT64ListCB::~UINT64ListCB() {}

void UINT64ListCB::updateFromCurSel() {
	int nIndex = SendMessage(_hWndCB, CB_GETCURSEL, 0, 0);
	UINT64 value = _aet->getUINT64(nIndex);
	_val->setUINT64Val(value);
}

void UINT64ListCB::updateFromValue() {
	for (int i = 0; i < _aet->nUINT64s(); i++) {
		if (_aet->getUINT64(i) == _val->getUINT64Val()) {
			SendMessage(_hWndCB, CB_SETCURSEL, i, 0);
		}
	}
}

int UINT64ListCB::getWidth() {
	return _w > _minW ? _w : _minW;
}

int UINT64ListCB::getHeight() {
	return _h > _minH ? _h : _minH;
}

void UINT64ListCB::setOrigin(int x, int y) {
	int w = getWidth();
	int h = getHeight();
	MoveWindow(_hwnd, _x = x, _y = y, w, h, TRUE);
}

void UINT64ListCB::updateSizeAllotment(int w, int h) {
	_w = w; _h = h;
	MoveWindow(_hwnd, _x, _y, w, h, TRUE);
}

HWND UINT64ListCB::getHWND() {
	return _hwnd;
}

HINSTANCE UINT64ListCB::getHInstance() {
	return _parent->getHInstance();
}

void UINT64ListCB::initialize(HINSTANCE hInstance) {
	_wc = { 0 };
	_wc.lpszClassName = L"UINT64ListCB";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = UINT64ListCB::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK UINT64ListCB::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {

	switch (msg) {
	case WM_DESTROY:
		DestroyWindow(hwnd);
		//PostQuitMessage(WM_QUIT);
		break;

	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			_aeui[hwnd]->updateFromCurSel();
			break;
		}
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}