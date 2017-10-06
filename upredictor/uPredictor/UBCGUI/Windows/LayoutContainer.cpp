#include "LayoutContainer.h"
#include <algorithm>

void LayoutContainer::addChild(LayoutElement *child) {
	std::vector<LayoutElement *>::iterator iter =
		find(_child.begin(), _child.end(), child);
	if (iter == _child.end()) {
		_child.push_back(child);
		onChildAdd(child);
	}
}

void LayoutContainer::clear() {
	/*
	int s = _child.size();
	for (int i = 0; i < s; i++) {
		LayoutElement *child = _child[i];
		delete child;
	}
	*/
	_child.clear();

	onClear();
}