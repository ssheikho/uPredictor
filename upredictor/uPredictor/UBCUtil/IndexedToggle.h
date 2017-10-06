#ifndef INDEXED_TOGGLE_H
#define INDEXED_TOGGLE_H

#include <cstdlib>

class IndexedToggle {
public:
	virtual void updateToggle(size_t index, bool val) = 0;
};

#endif
