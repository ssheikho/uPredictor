#ifndef POS_LINE_H
#define POS_LINE_H

#include "armposelistener.h"
#include "armposer.h"
#include "gridwrapper.h"

#include <gtk/gtk.h>

#include <vector>

using namespace std;

class GridWrapper;
//class PosGrid;
class PosList;

//Simply adds this line to PosGrid.  Easier to write as its own class.
class PosLine : public ArmPoseListener, public ArmPose {
	public:
		PosLine(PosList &pl, ArmPoser &ap,
				bool listen = true, bool frame = true,
				string border = "Current Arm Pose");
		~PosLine();

		GtkWidget *getWidget();
		GridWrapper &getGrid();

		void updatePose(ArmPose *pose);

		static void updateCB(GtkWidget *widget, gpointer data);
		static void moveCB(GtkWidget *widget, gpointer data);

		string getName();
		void setName(string name);
		int getNAngs();
		float getAng(int joint);
		void setAng(int joint, float val);

	protected:
		ArmPoser &_ap;
		GtkWidget *_label;
		vector<GtkEntry *> _entries;
		GtkWidget *_frame, *_updateButton, *_moveButton;
		GridWrapper _posGrid;
};

#endif
