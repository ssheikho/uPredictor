#ifndef GRID_LAYOUT_H
#define GRID_LAYOUT_H

#include "LayoutContainer.h"

#include <map>

using namespace std;

class GridLayout :
	public LayoutContainer {
public:
	// minW, minH no longer needed
	GridLayout(LayoutContainer *parent, int minW, int minH);
	~GridLayout();

	void addRow();

	GtkWidget *getWidget();
	void addChild(LayoutElement *child);	

protected:
	int _curRow, _curCol, _rows, _cols;

	GtkWidget *_grid;
};

#endif
