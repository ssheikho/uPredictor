#ifndef LAYOUT_ELEMENT_H
#define LAYOUT_ELEMENT_H

#include <gtk/gtk.h>
#include <gtk/gtkenums.h>

class LayoutElement {
public:
	virtual ~LayoutElement() = 0;
	
	virtual GtkWidget *getWidget() = 0;
};

#endif
