#ifndef GRID_WRAPPER_H
#define GRID_WRAPPER_H

#include <gtk/gtk.h>

#include <vector>

using namespace std;

class GridWrapper {
	public:

		GridWrapper();
		~GridWrapper();

		GtkWidget *getWidget();

		int addRow();
		void addChild(GtkWidget *widget, int colspan = 1, int row = -1);
		void skipChild();

		static gboolean setAlignRequest(gpointer data);
		void alignColumns(GridWrapper &gw);
		void addAlignRequest(GridWrapper *aligned);

	protected:
		//JWH - Not the most useful class at the moment, the idea is to store
		//		the metadata required in order to transform the grid
		//		in the event of row/column deletion or insertion in the middle
		//		somewhere
		class GridKid {
			public:
				GridKid(GtkWidget *widget, int colspan);
				~GridKid();

				GtkWidget *getWidget();
				int getColspan();

			protected:
				GtkWidget *_widget;
				int _colspan;
		};

		class GridRow {
			public:
				GridRow(GridWrapper *gw, int row);
				~GridRow();

				void addWidget(GridWrapper::GridKid *child);
				GtkWidget *getWidget(int col);
				GridWrapper::GridKid *getKid(int atCol);

				int getRow();
				int decRow();
				int incRow();
				int getCols();
				int getKids();
				int getWidth(int col);
				int getHeight(int col);
				int skipCol();

			protected:
				GridWrapper *_gw;
				int _row, _curCol;
				vector<GridWrapper::GridKid *> _v;
		};

		GtkWidget *_grid;
		vector<GridRow *> _rows;
		GridWrapper *_aligned;
};

#endif
