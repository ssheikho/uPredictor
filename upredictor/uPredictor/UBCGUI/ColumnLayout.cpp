#include "ColumnLayout.h"

ColumnLayout::ColumnLayout(LayoutContainer *parent, int minW, int minH) {
	_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	parent->addChild(this);
}

ColumnLayout::~ColumnLayout() {
	gtk_widget_destroy(_box);
}

GtkWidget *ColumnLayout::getWidget() {	return _box;	}

void ColumnLayout::addChild(LayoutElement *child) {
	gtk_box_pack_start(GTK_BOX(_box), child->getWidget(), TRUE, TRUE, 0);
}
