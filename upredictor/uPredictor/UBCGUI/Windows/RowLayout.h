#ifndef ROW_LAYOUT_H
#define ROW_LAYOUT_H

#include "LayoutContainer.h"

#include <map>

using namespace std;

class RowLayout : public LayoutContainer {
public:
	RowLayout(LayoutContainer *parent, int minW, int minH);
	~RowLayout();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	int getMaxWidth(LayoutElement *child);
	int getMaxHeight(LayoutElement *child);

	void updateSizeInfo(LayoutElement *child);;

	void prepareForSizeChanges();
	void postSizeChanges();

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	void onChildAdd(LayoutElement *child);
	void onClear();

	void layoutChildren();
	void addChildToLayout(LayoutElement *child);

	static WNDCLASSW _wc;
	static map<HWND, RowLayout *> _hcb;
	static bool _initialized;

	LayoutContainer *_parent;
	int _x, _y, _minW, _minH, _curW, _curH;
	HWND _hwnd;
};

#endif