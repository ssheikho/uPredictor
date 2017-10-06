#ifndef UBC_BUTTON_H
#define UBC_BUTTON_H

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
		string text, LayoutContainer *parent
		, IntSwitch *is, int actionIndex
		, int w, int h = 25);
	UBCButton(
		string text, LayoutContainer *parent
		, IndexedToggle *it, int actionIndex
		, int w, int h = 25);
	~UBCButton();

	GtkWidget *getWidget();

	void setTextD(double d, int precision = 1);
	void setTextI(long i);

	static void *click_event(GtkWidget *widget, void *data);

protected:
	void initialize(string text, bool checkbox);
	void updateAppropriately();

	LayoutContainer *_parent;
	IntSwitch *_is;
	IndexedToggle *_it;
	bool _isChecked;
	int _actionIndex, _w, _h;
	GtkWidget *_button;
};

#endif
