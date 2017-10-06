#ifndef NAME_CROSS_INDEX_H
#define NAME_CROSS_INDEX_H

#include <map>
#include <string>

class NameCrossIndex {
public:
	NameCrossIndex();
	~NameCrossIndex();

	void insert(std::string name, int index);

	std::string getNameAtIndex(int index);
	int getIndexWithName(std::string name);

	void printTable();

protected:
	std::map<std::string, int> _nameToIndex;
	std::map<int, std::string> _indexToName;

};

#endif
