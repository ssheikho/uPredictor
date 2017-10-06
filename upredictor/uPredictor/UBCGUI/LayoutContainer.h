#ifndef LAYOUT_CONTAINER_H
#define LAYOUT_CONTAINER_H

#include "LayoutElement.h"

#include <vector>

class LayoutContainer :
	public LayoutElement {
public:
	virtual void addChild(LayoutElement *child) = 0;
	//void clear();
	
protected:
	//virtual void onChildAdd(LayoutElement *child) = 0;
	//virtual void onClear() = 0;

	//std::vector<LayoutElement *> _child;
};

#endif
