#ifndef ROW_LAYOUT_H
#define ROW_LAYOUT_H

#include "LayoutContainer.h"

#include <map>

using namespace std;

class RowLayout : public LayoutContainer {
public:
	RowLayout(LayoutContainer *parent, int minW, int minH);
	~RowLayout();

	GtkWidget *getWidget();
	void addChild(LayoutElement *child);

protected:
	GtkWidget *_box;
};

#endif
