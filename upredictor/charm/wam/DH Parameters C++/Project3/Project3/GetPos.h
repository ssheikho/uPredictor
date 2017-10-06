#ifndef GETPOS_H
#define GETPOS_H

#include <deque>
#include <fstream>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <map>

using namespace std;

class GetPos {
	typedef deque <deque <double> > ::iterator record_iterator;
	typedef deque        <double>   ::iterator field_iterator;
	typedef map<int, string> markers;
	
	
public:	
	struct Trajectorie;
	const Trajectorie pos(const string& filename, const int& Frame);
	map<int, string> column(const string& filename);
	//bool savemarker(vector < tuple<int, string> > column);
	
};

#endif