#ifndef SCROLLING_WINDOW_H
#define SCROLLING_WINDOW_H

#include "LayoutContainer.h"

using namespace std;

class ScrollingWindow :
	public LayoutContainer {
public:
	// w, h are unused
	ScrollingWindow(LayoutContainer *parent, int w=0, int h=0);
	~ScrollingWindow();

	//LayoutElement
	GtkWidget *getWidget();

	//LayoutContainer
	void addChild(LayoutElement *child);

protected:
	LayoutContainer *_parent;

	GtkWidget *_widget;
	GtkWidget *_box;
};

#endif
