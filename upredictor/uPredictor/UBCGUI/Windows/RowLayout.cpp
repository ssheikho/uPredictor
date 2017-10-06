#include "RowLayout.h"

WNDCLASSW RowLayout::_wc;
map<HWND, RowLayout *> RowLayout::_hcb;
bool RowLayout::_initialized = false;

RowLayout::RowLayout(LayoutContainer *parent, int minW, int minH) :
_parent(parent), _x(0), _y(0), _minW(minW), _minH(minH), _curW(0), _curH(0) {
	if (!_initialized) initialize(parent->getHInstance());

	_hwnd = CreateWindowW(_wc.lpszClassName, L"RowLayout",
		WS_CHILD | WS_VISIBLE,
		_x, _y, _curW, _curH, _parent->getHWND(), 0,
		_parent->getHInstance(), NULL);

	parent->addChild(this);

	_hcb[_hwnd] = this;
}

RowLayout::~RowLayout() {
	DestroyWindow(_hwnd);
}

int RowLayout::getWidth() {
	int retVal = _curW > _minW ? _curW : _minW;
	return retVal;
}

int RowLayout::getHeight() {
	int retVal = _curH > _minH ? _curH : _minH;
	return retVal;
}

void RowLayout::setOrigin(int x, int y) {
	MoveWindow(_hwnd, _x = x, _y = y, getWidth(), getHeight(), TRUE);
}

void RowLayout::updateSizeAllotment(int w, int h) {
	_curW = w;
	_curH = h;
}

HWND RowLayout::getHWND() {
	return _hwnd;
}

HINSTANCE RowLayout::getHInstance() {
	return _parent->getHInstance();
}

int RowLayout::getMaxWidth(LayoutElement *child) {
	return -1;
}

int RowLayout::getMaxHeight(LayoutElement *child) {
	return -1;
}

void RowLayout::updateSizeInfo(LayoutElement *child) {
	layoutChildren();
	_parent->updateSizeInfo(this);
}

void RowLayout::prepareForSizeChanges() {

}

void RowLayout::postSizeChanges() {

}

void RowLayout::onChildAdd(LayoutElement *child) {
	addChildToLayout(child);
	_parent->updateSizeInfo(this);
}

void RowLayout::onClear() {
	layoutChildren();
}

void RowLayout::layoutChildren() {
	_curW = 0;
	for (int i = 0; i < _child.size(); i++)
		addChildToLayout(_child[i]);
}

void RowLayout::addChildToLayout(LayoutElement *child) {
	int h = getHeight();
	int w = getWidth();

	child->setOrigin(_curW, 0);
	_curW += child->getWidth();
	if (child->getHeight() > h) _curH = child->getHeight();

	MoveWindow(_hwnd, _x, _y, getWidth(), getHeight(), TRUE);
	if ((_curH > h) || (_curW > w)) {
		_parent->updateSizeInfo(this);
	}
}

void RowLayout::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"RowLayout";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = RowLayout::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK RowLayout::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}