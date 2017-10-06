#include "RowLayout.h"

RowLayout::RowLayout(LayoutContainer *parent, int minW, int minH) {
	_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	parent->addChild(this);
}

RowLayout::~RowLayout() {
	gtk_widget_destroy(_box);
}

GtkWidget *RowLayout::getWidget() {	return _box;	}

void RowLayout::addChild(LayoutElement *child) {
	gtk_box_pack_start(GTK_BOX(_box), child->getWidget(), TRUE, TRUE, 0);
}
