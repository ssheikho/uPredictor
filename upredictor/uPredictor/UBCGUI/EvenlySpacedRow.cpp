#include "EvenlySpacedRow.h"

WNDCLASSW EvenlySpacedRow::_wc;
map<HWND, EvenlySpacedRow *> EvenlySpacedRow::_esr;
bool EvenlySpacedRow::_initialized = false;

EvenlySpacedRow::EvenlySpacedRow(LayoutContainer *parent, int minW, int minH) :
	_parent(parent), _minW(minW), _minH(minH) {
	if (!_initialized) initialize(parent->getHInstance());
	_hwnd = CreateWindowW(_wc.lpszClassName, L"EvenlySpacedRow",
		WS_CHILD | WS_VISIBLE,
		0, 0, _minW, _minH, _parent->getHWND(), 0,
		_parent->getHInstance(), NULL);

	_parent->addChild(this);
}

EvenlySpacedRow::~EvenlySpacedRow() {
	DestroyWindow(_hwnd);
}

int EvenlySpacedRow::getWidth() {
	int w = _parent->getMaxWidth(this);
	return w > _minW ? w : _minW;
}

int EvenlySpacedRow::getHeight() {
	int h = _parent->getMaxHeight(this);
	return h > _minH ? h : _minH;
}

void EvenlySpacedRow::setOrigin(int x, int y) {
	MoveWindow(_hwnd, x, y, getWidth(), getHeight(), TRUE);
}

void EvenlySpacedRow::prepareForSizeChanges() {}

void EvenlySpacedRow::postSizeChanges() {}

void EvenlySpacedRow::updateSizeAllotment(int w, int h) {
	RECT r;
	GetWindowRect(_hwnd, &r);
	MoveWindow(_hwnd, r.left, r.top, getWidth(), getHeight(), TRUE);
	layoutChildren();
}

HWND EvenlySpacedRow::getHWND() {
	return _hwnd;
}

HINSTANCE EvenlySpacedRow::getHInstance() {
	return _parent->getHInstance();
}

int EvenlySpacedRow::getMaxWidth(LayoutElement *child) {
	return getWidth() / _child.size();
}

int EvenlySpacedRow::getMaxHeight(LayoutElement *child) {
	return getHeight();
}

void EvenlySpacedRow::updateSizeInfo(LayoutElement *child) {}

void EvenlySpacedRow::onChildAdd(LayoutElement *child) {
	layoutChildren();
}

void EvenlySpacedRow::onClear() {
	layoutChildren();
}

void EvenlySpacedRow::layoutChildren() {
	switch (_child.size()){
	case 0:
		break;
	case 1:
		oneChildSolution();
		break;
	case 2:
		twoChildSolution();
		break;
	default:
		multiChildSolution();
		break;
	}
}

void EvenlySpacedRow::oneChildSolution() {
	LayoutElement *child = _child[0];
	int cw = child->getWidth();
	int mw = getWidth();
	mw /= 2;
	mw -= cw / 2;
	child->setOrigin(mw, 0);
}

void EvenlySpacedRow::twoChildSolution() {
	_child[0]->setOrigin(0, 0);
	LayoutElement *child = _child[1];
	child->setOrigin(getWidth() - child->getWidth(), 0);
}

void EvenlySpacedRow::multiChildSolution() {
	LayoutElement *child;

	_child[0]->setOrigin(0, 0);

	float mw = (float)getWidth();
	mw /= (float)(_child.size() - 1);
	for (int childIndex = 1; childIndex < (_child.size() - 1); childIndex++) {
		LayoutElement *child = _child[childIndex];
		child->setOrigin((
			mw * (float)childIndex) - ((float)child->getWidth() / 2.0f),
			0);
	}
	
	child = _child[_child.size() - 1];
	child->setOrigin(getWidth() - child->getWidth(), 0);
}

void EvenlySpacedRow::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"EvenlySpacedRow";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = EvenlySpacedRow::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK EvenlySpacedRow::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}