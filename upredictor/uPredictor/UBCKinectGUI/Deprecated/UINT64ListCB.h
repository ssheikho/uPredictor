#ifndef UINT64LIST_CB_H
#define UINT64LIST_CB_H

#include "LayoutElement.h"

#include <map>

using namespace std;

class UINT64List;
class UINT64Value;
class LayoutContainer;

class UINT64ListCB :
	public LayoutElement {
public:
	UINT64ListCB(
		UINT64List *aet, UINT64Value *val,
		LayoutContainer *parent,
		int minW, int minH);
	~UINT64ListCB();

	void updateFromCurSel();
	void updateFromValue();

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//LayoutElement
	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

protected:
	static WNDCLASSW _wc;
	static map<HWND, UINT64ListCB *> _aeui;
	static bool _initialized;

	UINT64List *_aet;
	UINT64Value *_val;
	LayoutContainer *_parent;
	int _x, _y, _minW, _minH, _w, _h;

	HWND _hwnd, _hWndCB;
};

#endif