#include "UBCButton.h"
//#include "IntegerIndicator.h"
#include "IndexedToggle.h"
#include "IntSwitch.h"
#include "LayoutContainer.h"
#include "UBCUtil.h"

WNDCLASSW UBCButton::_wc;
map<HWND, UBCButton *> UBCButton::_hcb;
bool UBCButton::_initialized = false;

UBCButton::UBCButton(
	wstring text, LayoutContainer *parent
	, IntSwitch *is, int actionIndex
	, int w, int h) :
	_parent(parent)
	, _is(is)
	, _it(NULL)
	, _isChecked(false)
	, _actionIndex(actionIndex)
	, _w(w)
	, _h(h) {
	initialize(text, false);
}

UBCButton::UBCButton(
	wstring text, LayoutContainer *parent
	, IndexedToggle *it, int actionIndex
	, int w, int h) :
	_parent(parent)
	, _is(NULL)
	, _it(it)
	, _isChecked(false)
	, _actionIndex(actionIndex)
	, _w(w)
	, _h(h) {
	initialize(text, true);
}

void UBCButton::initialize(wstring text, bool checkbox) {
	if (!_initialized) initialize(_parent->getHInstance());

	_hwnd = CreateWindow(_wc.lpszClassName, text.c_str(),
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		0, 0, _w, _h, _parent->getHWND(), (HMENU)2, _parent->getHInstance(), NULL);

	_hwndB = CreateWindow(L"BUTTON", text.c_str(),
		checkbox ?
		WS_BORDER | WS_CHILD | WS_VISIBLE | BS_CHECKBOX :
		WS_BORDER | WS_CHILD | WS_VISIBLE
		, 0, 0, _w, _h, _hwnd, (HMENU)2, _parent->getHInstance(), NULL);

	_parent->addChild(this);

	_hcb[_hwnd] = this;
}

UBCButton::~UBCButton() {
	DestroyWindow(_hwndB);
	DestroyWindow(_hwnd);
}

int UBCButton::getWidth() {
	return _w;
}

int UBCButton::getHeight() {
	return _h;
}

void UBCButton::setOrigin(int x, int y) {
	MoveWindow(_hwnd, x, y, _w, _h, TRUE);
}

void UBCButton::updateSizeAllotment(int w, int h) {}

HWND UBCButton::getHWND() {
	return _hwnd;
}

HINSTANCE UBCButton::getHInstance() {
	return _parent->getHInstance();
}

void UBCButton::setTextD(double d, int precision) {
	SetWindowText(_hwnd, doubleToWString(d, precision).c_str());
}

void UBCButton::setTextI(long i) {
	SetWindowText(_hwnd, intToWString(i).c_str());
}

/*
void AutoResizeButton::updateII(IntegerIndicator *ii) {
	setTextI(ii->intVal());
}
*/

void UBCButton::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"AutoResizeButton";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = UBCButton::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK UBCButton::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	map<HWND, UBCButton *>::iterator iter = _hcb.find(hwnd);
	if (iter != _hcb.end()) {
		UBCButton *arb = iter->second;

		switch (msg) {
		case WM_COMMAND:
			arb->updateAppropriately();
			break;
		}
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void UBCButton::updateAppropriately() {
	if (_is) {
		_is->updateSwitch(_actionIndex);
	}
	else {
		_isChecked = !_isChecked;
		SendMessage(_hwndB, BM_SETCHECK
			, _isChecked ? BST_CHECKED : BST_UNCHECKED, 0);
		_it->updateToggle(_actionIndex, _isChecked);
	}
}