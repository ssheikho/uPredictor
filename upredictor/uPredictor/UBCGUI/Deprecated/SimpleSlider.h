#ifndef SIMPLE_SLIDER_H
#define SIMPLE_SLIDER_H

#include "IntValueArray.h"
#include "IntValueArrayListener.h"
#include "LayoutElement.h"

#include <map>
#include <memory>

using namespace std;

class IntValueArray;
class LayoutContainer;

class SimpleSlider :
	public IntValueArray
	, public IntValueArrayListener
	, public LayoutElement
{
public:
	SimpleSlider(
		LayoutContainer *parent, int w, int h,
		IntValueArray *controlled, int controlledIndex,
		bool deleteControlledIVAAtEnd,
		IntValueArray *listeningTo = NULL,
		int listenIndex = -1);
	virtual ~SimpleSlider();

	void updateFromSrc();
	void updateFromSlider();

	//From IntValueArray
	void set(int index, int value, void *origin);
	int get(int index);

	bool hasMin(int index);
	bool hasMax(int index);
	int getMinVal(int index);
	int getMaxVal(int index);

	size_t getNVals();

	//From IntValueArrayListener
	void updateIVAL(IntValueArray *iva, int index, int value,
		void *origin);

	//From LayoutElement
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
	static map<HWND, SimpleSlider *> _ss;
	static bool _initialized;

	LayoutContainer *_parent;
	IntValueArray *_controlled, *_listeningTo;
	int _w, _h, _controlledIndex, _listenIndex, _curVal;
	bool _deleteControlledIVAAtEnd;
	HWND _hwnd, _frameTB;
};

#endif