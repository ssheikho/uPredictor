#include "SimpleComboBox.h"
#include "LayoutContainer.h"

#include <CommCtrl.h>

WNDCLASSW SimpleComboBox::_wc;
map<HWND, SimpleComboBox *> SimpleComboBox::_hcb;
bool SimpleComboBox::_initialized = false;

SimpleComboBox::SimpleComboBox(
	LayoutContainer *parent
	, int w
	, int h
	, int hLine) :
_parent(parent), _w(w), _h(h), _hLine(hLine)
{
	if (!_initialized) initialize(_parent->getHInstance());

	_hwnd = CreateWindow(_wc.lpszClassName, L"",
		WS_BORDER | WS_CHILD | WS_VISIBLE,
		0, 0, w, _hLine, _parent->getHWND(), (HMENU)2, parent->getHInstance(), NULL);

	_hwndB = CreateWindow(WC_COMBOBOX, TEXT(""),
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		0, 0, _w, _h, _hwnd, NULL, parent->getHInstance(),
		NULL);
	
	parent->addChild(this);

	_hcb[_hwnd] = this;
	_hcb[_hwndB] = this;

}

SimpleComboBox::~SimpleComboBox() {}

void SimpleComboBox::addSelection(wstring label, long value) {
	SendMessage(_hwndB, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)label.c_str());
	_selections.push_back(value);
}

// Sets the default selected value
void SimpleComboBox::setSelectedValue(long value) {
	SendMessage(_hwndB, (UINT)CB_SETCURSEL, (WPARAM)value, (LPARAM)0);
}

void SimpleComboBox::sendSelectedValue() {
	int index = SendMessage((HWND)_hwndB, (UINT)CB_GETCURSEL,
		(WPARAM)0, (LPARAM)0);
	if((index >= 0) && (index < _selections.size()))
		fireUpdate(_selections[index]);
}

size_t SimpleComboBox::getNVals() {
	return _selections.size();
}

//LayoutElement
int SimpleComboBox::getWidth() {
	return _w;
}

int SimpleComboBox::getHeight() {
	return _hLine;
}

void SimpleComboBox::setOrigin(int x, int y) {
	MoveWindow(_hwnd, x, y, _w, _hLine, TRUE);
}

void SimpleComboBox::updateSizeAllotment(int w, int h) {
	_w = w;
	_hLine = h;
}

HWND SimpleComboBox::getHWND() {
	return _hwnd;
}

HINSTANCE SimpleComboBox::getHInstance() {
	return _parent->getHInstance();
}

void SimpleComboBox::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"SimpleComboBox";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = SimpleComboBox::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK SimpleComboBox::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	map<HWND, SimpleComboBox *>::iterator iter = _hcb.find(hwnd);
	if (iter != _hcb.end()) {
		SimpleComboBox *arb = iter->second;

		switch (msg) {
		case WM_COMMAND:
			arb->sendSelectedValue();
			break;
		}
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}