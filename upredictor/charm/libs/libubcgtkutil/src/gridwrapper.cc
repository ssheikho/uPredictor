#include "gridwrapper.h"

#include <iostream>

using namespace std;

GridWrapper::GridWrapper() : _grid(gtk_grid_new()), _aligned(NULL) {}
GridWrapper::~GridWrapper() {}

GtkWidget *GridWrapper::getWidget()	{	return _grid;	}

int GridWrapper::addRow() {
	_rows.push_back(new GridWrapper::GridRow(this, _rows.size()));
	return _rows.size() - 1;
}

void GridWrapper::addChild(GtkWidget *widget, int colspan, int row) {
	int r = row == -1 ? _rows.size() - 1 : row;
	_rows[r]->addWidget(new GridWrapper::GridKid(widget, colspan));
}

void GridWrapper::skipChild() {
	_rows[_rows.size() - 1]->skipCol();
}

gboolean GridWrapper::setAlignRequest(gpointer data) {
	GridWrapper *gw = (GridWrapper *)data;
	gw->alignColumns(*gw->_aligned);
	return FALSE;
}

void GridWrapper::alignColumns(GridWrapper &gw) {
	int fromCol = 0;
	for(int i = 0; i < _rows[0]->getKids(); i++) {
		int widthReq = 0;
		int heightReq = gw._rows[0]->getHeight(fromCol);
		GridWrapper::GridKid *gk = _rows[0]->getKid(i);
		
		if(gk) {
			for(int j = 0; j < gk->getColspan(); j++)
				widthReq += gw._rows[0]->getWidth(fromCol++);

			gtk_widget_set_size_request(gk->getWidget(), widthReq, heightReq);
		}
	}
}

void GridWrapper::addAlignRequest(GridWrapper *aligned) {
	_aligned = aligned;
	g_idle_add(setAlignRequest, this);
}

GridWrapper::GridKid::GridKid(GtkWidget *widget, int colspan) :
	_widget(widget), _colspan(colspan) {}

GridWrapper::GridKid::~GridKid() {}

GtkWidget *GridWrapper::GridKid::getWidget()	{	return _widget;		}
int GridWrapper::GridKid::getColspan()			{	return _colspan;	}

GridWrapper::GridRow::GridRow(GridWrapper *gw, int row) : _gw(gw), _row(row),
	_curCol(0) {}
GridWrapper::GridRow::~GridRow() {}

void GridWrapper::GridRow::addWidget(GridWrapper::GridKid *child) {
	_v.push_back(child);
	gtk_grid_attach((GtkGrid *)_gw->_grid, child->getWidget(),
		_curCol, _row, child->getColspan(), 1);
	_curCol += child->getColspan();
}

GridWrapper::GridKid *GridWrapper::GridRow::getKid(int atCol) {
	return _v[atCol];
}

GtkWidget *GridWrapper::GridRow::getWidget(int col) {
	return _v[col]->getWidget();
}

int GridWrapper::GridRow::getRow()				{	return _row;		}
int GridWrapper::GridRow::decRow()				{	return --_row;		}
int GridWrapper::GridRow::incRow()				{	return ++_row;		}
int GridWrapper::GridRow::getCols()				{	return _curCol;		}
int GridWrapper::GridRow::getKids()				{	return _v.size();	}
int GridWrapper::GridRow::skipCol()				{	return ++_curCol;	}

int GridWrapper::GridRow::getWidth(int col) {
	return gtk_widget_get_allocated_width(_v[col]->getWidget());
}

int GridWrapper::GridRow::getHeight(int col) {
	return gtk_widget_get_allocated_height(_v[col]->getWidget());
}
