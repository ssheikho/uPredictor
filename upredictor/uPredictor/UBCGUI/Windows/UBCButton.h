#ifndef UBC_BUTTON_H
#define UBC_BUTTON_H

#include <WinSock2.h>
#include <Windows.h>

//#include "IntegerIndicatorListener.h"
#include "LayoutElement.h"

#include <map>

using namespace std;

class LayoutContainer;
class IndexedToggle;
class IntSwitch;

class UBCButton :
	public LayoutElement
	//, public IntegerIndicatorListener
{
public:
	UBCButton(
		wstring text, LayoutContainer *parent
		, IntSwitch *is, int actionIndex
		, int w, int h = 25);
	UBCButton(
		wstring text, LayoutContainer *parent
		, IndexedToggle *it, int actionIndex
		, int w, int h = 25);
	~UBCButton();

	int getWidth();
	int getHeight();
	void setOrigin(int x, int y);
	void updateSizeAllotment(int w, int h);
	HWND getHWND();
	HINSTANCE getHInstance();

	void setTextD(double d, int precision = 1);
	void setTextI(long i);

	//void updateII(IntegerIndicator *ii);

	static void initialize(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	void initialize(wstring text, bool checkbox);
	void updateAppropriately();

	static WNDCLASSW _wc;
	static map<HWND, UBCButton *> _hcb;
	static bool _initialized;

	LayoutContainer *_parent;
	IntSwitch *_is;
	IndexedToggle *_it;
	bool _isChecked;
	int _actionIndex, _w, _h;
	HWND _hwnd, _hwndB;
};

#endif