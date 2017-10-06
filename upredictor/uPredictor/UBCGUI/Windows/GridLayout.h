#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#include "LayoutContainer.h"

#include <map>

using namespace std;

class GridLayout :
	public LayoutContainer {
public:
	GridLayout(LayoutContainer *parent, int minW, int minH);
	~GridLayout();

	void addRow();
	void positionChild(LayoutElement *child, int cellX, int cellY);

	//LayoutElement::LayoutContainer
	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	//LayoutContainer
	int getMaxWidth(LayoutElement *child);
	int getMaxHeight(LayoutElement *child);

	void updateSizeInfo(LayoutElement *child);

	void prepareForSizeChanges();
	void postSizeChanges();

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
protected:
	void onChildAdd(LayoutElement *child);
	void onClear();

	void computeRowColSizes();
	void layoutChildren();

	static WNDCLASSW _wc;
	static map<HWND, GridLayout *> _hcb;
	static bool _initialized;
	
	LayoutContainer *_parent;
	int _x, _y, _minW, _minH, _curW, _curH, _prevRow, _prevCol, _rows, _cols;
	HWND _hwnd;

	map < pair<int, int>, LayoutElement *> _gridKids;
	map <LayoutElement *, pair<int, int>> _kidCells;
	//vector<vector<LayoutElement *>> _elements;
	vector<int> _colWidths, _rowHeights;

};

#endif