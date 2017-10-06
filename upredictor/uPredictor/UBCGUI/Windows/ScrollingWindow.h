#ifndef SCROLLING_WINDOW_H
#define SCROLLING_WINDOW_H

#include "LayoutContainer.h"

#include <map>

using namespace std;

class ScrollingWindow :
	public LayoutContainer {
public:
	ScrollingWindow(LayoutContainer *parent, int w, int h);
	~ScrollingWindow();

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//LayoutElement
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

protected:
	static bool _initialized;
	static WNDCLASSW _wc, _wcScroll;
	static map<HWND, ScrollingWindow *> _sw;

	void onChildAdd(LayoutElement *child);
	void onClear();

	void updateScrollbarHeight();
	void updateScrollbarPos(int pos);
	void updateScrollbarLineUp();
	void updateScrollbarLineDown();

	LayoutContainer *_parent;
	int _x, _y, _w, _h, _vScroll, _spareScroll;// , _sbPos;
	SCROLLINFO _si;
	bool _antiFlash;

	HWND _hwnd, _hScroll;
};

#endif