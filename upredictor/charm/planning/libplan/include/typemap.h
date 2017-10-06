#ifndef TYPE_MAP_H
#define TYPE_MAP_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class TypeMap {
	public:
		TypeMap();
		~TypeMap();

		void insert(string name);
		int size();

		string getName(int i);
		int getIndex(string name);

		void printContents();

	protected:
		vector<string> _v;
		map<string, int> _m;
		int _ctr;
};

#endif
