#include "UBCEntry.h"
//#include "IntegerIndicator.h"
//#include "IntValueArray.h"
#include "LayoutContainer.h"
#include "UBCUtil.h"

WNDCLASSW UBCEntry::_wc;
map<HWND, UBCEntry *> UBCEntry::_hcb;
bool UBCEntry::_initialized = false;

UBCEntry::UBCEntry(wstring text, LayoutContainer *parent,
	bool entry,	int w, int h) :
	_text(text),
	_parent(parent), _x(0), _y(0), _w(w), _h(h)
	, _valIsStored(false)
	//, _ivaIndex(-1), _minValMax(-1)
{
	if (!_initialized) initialize(_parent->getHInstance());

	_hwnd = CreateWindow(_wc.lpszClassName, text.c_str(),
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		0, 0, w, h, _parent->getHWND(), (HMENU)2, parent->getHInstance(), NULL);

	_hwndE = CreateWindow(entry ? L"EDIT" : L"STATIC", _text.c_str(),
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		_x, _y, _w, _h, _hwnd, (HMENU)2, parent->getHInstance(), NULL);

	parent->addChild(this);

	_hcb[_hwnd] = this;
	//_hcb[_hwndE] = this;
}

UBCEntry::~UBCEntry() {
	//DestroyWindow(_hwndE);
	DestroyWindow(_hwnd);
	//CloseHandle(_hwnd);
}

int UBCEntry::getWidth() {
	return _w;
}

int UBCEntry::getHeight() {
	return _h;
}

void UBCEntry::setOrigin(int x, int y) {
	_x = x;
	_y = y;
	MoveWindow(_hwnd, _x, _y, _w, _h, TRUE);
}

void UBCEntry::updateSizeAllotment(int w, int h) {
	MoveWindow(_hwnd, _x, _y, _w = w, _h = h, TRUE);
}

HWND UBCEntry::getHWND() {
	return _hwnd;
}

HINSTANCE UBCEntry::getHInstance() {
	return _parent->getHInstance();
}

wstring UBCEntry::getTextW() {
	wchar_t s[100];
	GetWindowText(_hwndE, s, 100);
	_text = s;
	return _text;
}

string UBCEntry::getTextS() {
	return wstringToString(getTextW());
}

double UBCEntry::getTextD() {
	return strtod(getTextS().c_str(), NULL);
}

void UBCEntry::setTextD(double d, int precision) {
	_text = thingToWString<double>(d, precision);
	//if (!_valIsStored)
	SetWindowText(_hwndE, _text.c_str());
	//_valIsStored = true;
	// doubleToWString(d, precision);
}

void UBCEntry::setTextI(long i) {
	_text = intToWString(i);
	//if(!_valIsStored)
	SetWindowText(_hwndE, _text.c_str());
	//_valIsStored = true;
}

void UBCEntry::processType(double t) {
	setTextD(t, 3);
}

void UBCEntry::processType(long t) {
	setTextI(t);
}

void UBCEntry::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"UBCEntry";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = UBCEntry::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK UBCEntry::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	map<HWND, UBCEntry *>::iterator iter = _hcb.find(hwnd);
	if (iter != _hcb.end()) {
		UBCEntry *arb = iter->second;
		arb->_valIsStored = false;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}