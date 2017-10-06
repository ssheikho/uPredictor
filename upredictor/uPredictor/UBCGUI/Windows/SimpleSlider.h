#ifndef SIMPLE_SLIDER_H
#define SIMPLE_SLIDER_H

#include "LayoutElement.h"
#include "TypeBroadcaster.h"
#include "TypeRecipient.h"

#include <map>
#include <memory>

using namespace std;

class IntValueArray;
class LayoutContainer;

class SimpleSlider :
	public TypeRecipient<long>
	, public TypeBroadcaster<long>
	, public TypeRecipient<double>
	, public TypeBroadcaster<double>
	, public LayoutElement
{
public:
	SimpleSlider(
		LayoutContainer *parent
		, int w
		, int h
		, long minVal
		, long maxVal
		, long startVal
		, double scaleVal = 1.0
		);
	virtual ~SimpleSlider();

	void updateFromSrc();
	void updateFromSlider();

	void set(long val);
	long get();
	long getMin();
	long getMax();

	//From TypeRecipient<long>
	void processType(long t);
	void processType(double t);
	void TypeRecipient<long>::onStartup() {}
	void TypeRecipient<double>::onStartup() {}

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
	int _w, _h;
	long _minVal, _maxVal, _curVal;
	double _scaleVal;
	HWND _hwnd, _frameTB;
};

#endif
