#ifndef SIMPLE_COMBO_BOX_H
#define SIMPLE_COMBO_BOX_H

#include <WinSock2.h>
#include <Windows.h>

#include "LayoutElement.h"
#include "TypeBroadcaster.h"

#include <map>
#include <vector>

using namespace std;

class LayoutContainer;

class SimpleComboBox :
	public LayoutElement
	, public TypeBroadcaster<long>
{
public:
	SimpleComboBox(
		LayoutContainer *parent
		, int w
		, int h
		, int hLine
		);

	~SimpleComboBox();

	void addSelection(wstring label, long value);
	void setSelectedValue(long value);
	void sendSelectedValue();
	size_t getNVals();

	//LayoutElement
	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	static WNDCLASSW _wc;
	static map<HWND, SimpleComboBox *> _hcb;
	static bool _initialized;

	LayoutContainer *_parent;
	int _w, _h, _hLine;
	HWND _hwnd, _hwndB;

	vector<long> _selections;
};

#endif