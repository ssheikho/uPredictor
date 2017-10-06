#ifndef LAYOUT_CONTAINER_H
#define LAYOUT_CONTAINER_H

#include "LayoutElement.h"

#include <vector>

class LayoutContainer :
	public LayoutElement {
public:
	//virtual ~LayoutContainer() = 0;

	//LayoutElement
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual void setOrigin(int x, int y) = 0;
	virtual HWND getHWND() = 0;
	virtual HINSTANCE getHInstance() = 0;

	//LayoutContainer
	virtual int getMaxWidth(LayoutElement *child) = 0;
	virtual int getMaxHeight(LayoutElement *child) = 0;

	virtual void updateSizeInfo(LayoutElement *child) = 0;

	virtual void prepareForSizeChanges() = 0;
	virtual void postSizeChanges() = 0;

	void addChild(LayoutElement *child);
	void clear();
	
protected:
	virtual void onChildAdd(LayoutElement *child) = 0;
	virtual void onClear() = 0;

	std::vector<LayoutElement *> _child;
};

#endif