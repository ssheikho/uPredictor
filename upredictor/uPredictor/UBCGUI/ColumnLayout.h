#ifndef COLUMN_LAYOUT_H
#define COLUMN_LAYOUT_H

#include "LayoutContainer.h"

#include <map>

using namespace std;

class ColumnLayout : public LayoutContainer {
public:
	ColumnLayout(LayoutContainer *parent, int minW, int minH);
	~ColumnLayout();

	GtkWidget *getWidget();
	void addChild(LayoutElement *child);

protected:
	GtkWidget *_box;
};

#endif
