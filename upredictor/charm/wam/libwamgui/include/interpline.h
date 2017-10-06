#ifndef INTERP_LINE_H
#define INTERP_LINE_H

#include "gridwrapper.h"

class InterpLine {
	public:
		InterpLine();
		~InterpLine();

		GtkWidget *getWidget();

	protected:
		GridWrapper _gw;
};

#endif
