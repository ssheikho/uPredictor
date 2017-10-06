#ifndef SIMPLE_LOAD_SAVE_H
#define SIMPLE_LOAD_SAVE_H

#include <string>

using namespace std;

class SimpleLoadSave {
public:
	virtual void load(string filename) = 0;
	virtual void save(string filename) = 0;
};

#endif
