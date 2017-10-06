#ifndef POS_LIST_CB_H
#define POS_LIST_CB_H

#include "gridwrapper.h"

#include <string>

using namespace std;

class ArmPoser;
class PosList;

class PosListCB {
	public:
		PosListCB(PosList &pl, string filename, bool frame = true);
		~PosListCB();

		GtkWidget *getWidget();
		GridWrapper &getGrid();

		static void loadCB(GtkWidget *widget, gpointer data);
		static void saveCB(GtkWidget *widget, gpointer data);
		static void addLineCB(GtkWidget *widget, gpointer data);

	protected:
		void load();
		void save();
		void addLine();
	
		PosList &_pl;

		GridWrapper _gw;

		GtkEntry	*_filenameEntry;
		GtkWidget	*_frame, *_loadButton, *_saveButton, *_addLineButton;
};

#endif
