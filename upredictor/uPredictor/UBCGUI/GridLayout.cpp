#include "GridLayout.h"

GridLayout::GridLayout(LayoutContainer *parent, int minW, int minH) :
_curRow(0), _curCol(0), _rows(1), _cols(1) {
	_grid = gtk_grid_new();
	parent->addChild(this);
}

GridLayout::~GridLayout() {
	gtk_widget_destroy(_grid);
}

void GridLayout::addRow() {
	_curCol = 0;
	_curRow++;
	gtk_grid_insert_row(GTK_GRID(_grid), _rows++);
}

GtkWidget *GridLayout::getWidget() {
	return _grid;
}

void GridLayout::addChild(LayoutElement *child) {
	if (_curCol >= _cols) {
		gtk_grid_insert_column(GTK_GRID(_grid), _cols++);
	}
	gtk_grid_attach(GTK_GRID(_grid), child->getWidget(),
			_curCol++, _curRow, 1, 1);	
}

