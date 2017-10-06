#ifndef EVENLY_SPACED_ROW_H
#define EVENLY_SPACED_ROW_H

#include "LayoutContainer.h"

#include <map>

using namespace std;

class EvenlySpacedRow :
	public LayoutContainer {
public:
	EvenlySpacedRow(LayoutContainer *parent, int minW, int minH);
	~EvenlySpacedRow();

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
	void onChildAdd(LayoutElement *child);
	void onClear();

	void layoutChildren();
	void oneChildSolution();
	void twoChildSolution();
	void multiChildSolution();

	static WNDCLASSW _wc;
	static map<HWND, EvenlySpacedRow *> _esr;
	static bool _initialized;

	LayoutContainer *_parent;
	int _minW, _minH;
	HWND _hwnd;
};

#endif