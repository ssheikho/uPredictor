#include "ColumnLayout.h"

WNDCLASSW ColumnLayout::_wc;
map<HWND, ColumnLayout *> ColumnLayout::_hcb;
bool ColumnLayout::_initialized = false;

ColumnLayout::ColumnLayout(LayoutContainer *parent, int minW, int minH) :
_parent(parent), _x(0), _y(0), _minW(minW), _minH(minH), _curW(0), _curH(0) {
	if (!_initialized) initialize(parent->getHInstance());

	_hwnd = CreateWindowW(_wc.lpszClassName, L"ColumnLayout",
		//WS_CHILD | WS_VISIBLE,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		_x, _y, minW, minH, _parent->getHWND(), 0,
		_parent->getHInstance(), NULL);

	_parent->prepareForSizeChanges();
	parent->addChild(this);
	_parent->postSizeChanges();

	_hcb[_hwnd] = this;
}

ColumnLayout::~ColumnLayout() {
	DestroyWindow(_hwnd);
}

int ColumnLayout::getWidth() {
	return _curW > _minW ? _curW : _minW;
}

int ColumnLayout::getHeight() {
	int h = _curH > _minH ? _curH : _minH;;
	return h;
}

void ColumnLayout::setOrigin(int x, int y) {
	int w = getWidth();
	int h = getHeight();
	MoveWindow(_hwnd, _x = x, _y  = y, w, h, TRUE);
}

void ColumnLayout::updateSizeAllotment(int w, int h) {
	_curW = w;
	_curH = h;
	for (int i = 0; i < _child.size(); i++) _child[i]->updateSizeAllotment(w, -1);
}
 
HWND ColumnLayout::getHWND() {
	return _hwnd;
}

HINSTANCE ColumnLayout::getHInstance() {
	return _parent->getHInstance();
}

int ColumnLayout::getMaxWidth(LayoutElement *child) {
	return getWidth();
}

int ColumnLayout::getMaxHeight(LayoutElement *child) {
	return getHeight();
}

void ColumnLayout::prepareForSizeChanges() {

}

void ColumnLayout::postSizeChanges() {

}

void ColumnLayout::updateSizeInfo(LayoutElement *child) {
	layoutChildren();
}

void ColumnLayout::onChildAdd(LayoutElement *child) {
	//child->updateSizeAllotment(getWidth(), -1);
	layoutChildren();
}

void ColumnLayout::layoutChildren() {
	_parent->prepareForSizeChanges();
	_curH = 0;
	int s = _child.size();
	for (int i = 0; i < s; i++)
		addChildToLayout(_child[i]);
	_parent->updateSizeInfo(this);
	_parent->postSizeChanges();
}

void ColumnLayout::addChildToLayout(LayoutElement *child) {
	child->setOrigin(0, _curH);
	_curH += child->getHeight();
	if (child->getWidth() > _curW) _curW = child->getWidth();

	int h = getHeight();
	int w = getWidth();
	MoveWindow(_hwnd, _x, _y, w, h, TRUE);
	_parent->updateSizeInfo(this);
}

void ColumnLayout::onClear() {
	layoutChildren();
}

void ColumnLayout::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"ColumnLayout";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = ColumnLayout::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK ColumnLayout::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}