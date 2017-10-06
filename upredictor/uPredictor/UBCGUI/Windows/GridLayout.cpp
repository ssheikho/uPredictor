#include "GridLayout.h"

WNDCLASSW GridLayout::_wc;
map<HWND, GridLayout *> GridLayout::_hcb;
bool GridLayout::_initialized = false;

GridLayout::GridLayout(LayoutContainer *parent, int minW, int minH) :
_parent(parent)
, _x(0), _y(0)
, _minW(minW), _minH(minH)
, _curW(0), _curH(0),
_prevRow(-1), _prevCol(-1)
, _rows(0), _cols(0) {
	if (!_initialized) initialize(parent->getHInstance());

	_hwnd = CreateWindowW(_wc.lpszClassName, L"GridLayout",
		//WS_CHILD | WS_VISIBLE,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		0, 0, _minW, _minH, _parent->getHWND(), 0,
		_parent->getHInstance(), NULL);

	_parent->addChild(this);
}

GridLayout::~GridLayout() {
	DestroyWindow(_hwnd);
}

void GridLayout::initialize(HINSTANCE hInstance) {
	_initialized = true;

	_wc = { 0 };
	_wc.lpszClassName = L"GridLayout";
	_wc.hInstance = hInstance;
	_wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//_wc.hbrBackground = GetSysColorBrush(COLOR_ACTIVECAPTION);
	_wc.lpfnWndProc = GridLayout::WndProc;
	_wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&_wc);
}

LRESULT CALLBACK GridLayout::WndProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam) {
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int GridLayout::getWidth() {
	return _curW > _minW ? _curW : _minW;
}

int GridLayout::getHeight() {
	return _curH > _minH ? _curH : _minH;
}

void GridLayout::setOrigin(int x, int y) {
	MoveWindow(_hwnd, _x = x, _y = y, getWidth(), getHeight(), TRUE);
}

void GridLayout::updateSizeAllotment(int w, int h) {
	MoveWindow(_hwnd, _x, _y, getWidth(), getHeight(), TRUE);
}

HWND GridLayout::getHWND() {
	return _hwnd;
}

HINSTANCE GridLayout::getHInstance() {
	return _parent->getHInstance();
}

int GridLayout::getMaxWidth(LayoutElement *child) {
	return -1;
}

int GridLayout::getMaxHeight(LayoutElement *child) {
	return -1;
}

void GridLayout::prepareForSizeChanges() {}

void GridLayout::postSizeChanges() {}

void GridLayout::updateSizeInfo(LayoutElement *child) {
	layoutChildren();
}

void GridLayout::addRow() {
	_prevCol = -1;
	_prevRow = _rows++;
}

void GridLayout::positionChild(LayoutElement *child, int cellX, int cellY) {}

void GridLayout::onChildAdd(LayoutElement *child) {
	_gridKids[pair<int, int>(_prevRow, ++_prevCol)] = child;
	if (_prevCol + 1 > _cols) _cols = _prevCol + 1;
	layoutChildren();
}

void GridLayout::onClear() {
	layoutChildren();
}

void GridLayout::computeRowColSizes() {
	for (int row = 0; row < _rows; row++) {
		if (_rowHeights.size() <= row) {
			_rowHeights.push_back(0);
		}
		else {
			_rowHeights[row] = 0;
		}
	}
	for (int col = 0; col < _cols; col++) {
		if (_colWidths.size() <= col) {
			_colWidths.push_back(0);
		}
		else {
			_colWidths[col] = 0;
		}
	}

	for (int row = 0; row < _rows; row++) {
		for (int col = 0; col < _cols; col++) {
			pair<int, int> index(row, col);
			map < pair<int, int>, LayoutElement *>::iterator iter =
				_gridKids.find(index);
			if (iter != _gridKids.end()) {
				LayoutElement *kid = iter->second;
				int kW = kid->getWidth();
				int kH = kid->getHeight();
				if (kH > _rowHeights[row])	_rowHeights[row] = kH;
				if (kW > _colWidths[col])	_colWidths[col] = kW;
			}
		}
	}

	_curH = 0;
	_curW = 0;
	for (int row = 0; row < _rows; row++) {
		int h = _rowHeights[row];
		_curH += h;
	}
	for (int col = 0; col < _cols; col++)
		_curW += _colWidths[col];

	_parent->updateSizeInfo(this);
}

void GridLayout::layoutChildren() {
	computeRowColSizes();

	int curX = 0;
	int curY = 0;
	for (int row = 0; row < _rows; row++) {
		curX = 0;
		for (int col = 0; col < _cols; col++) {
			pair<int, int> index(row, col);
			map < pair<int, int>, LayoutElement *>::iterator iter =
				_gridKids.find(index);
			if (iter != _gridKids.end())
				iter->second->setOrigin(curX, curY);

			curX += _colWidths[col];
		}
		curY += _rowHeights[row];
	}
	MoveWindow(_hwnd, _x, _y, getWidth(), getHeight(), TRUE);
}