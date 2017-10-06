#ifndef SIMPLE_COMBO_BOX_H
#define SIMPLE_COMBO_BOX_H

// #include <WinSock2.h>
// #include <Windows.h>

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
		//, int w
		//, int h
		//, int hLine
		);

	~SimpleComboBox();

	void addSelection(string label, long value);
	void setSelectedValue(long value);
	void sendSelectedValue();
	size_t getNVals();
	
	static void valueChanged(GtkComboBox *cb, gpointer user_data);

	//LayoutElement
	GtkWidget *getWidget();

protected:
	static bool _initialized;

	LayoutContainer *_parent;
	//int _w, _h, _hLine;

	GtkWidget* _comboBox;

	vector<long> _selections;
};

#endif
