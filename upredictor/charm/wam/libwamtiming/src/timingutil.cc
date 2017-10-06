#include "timingutil.h"

#include <sstream>

vector<string> split(const string &s, char delim) {
	vector<string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
