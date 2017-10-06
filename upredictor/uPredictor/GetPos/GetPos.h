#pragma once
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
#include <list>

using namespace std;

class GetPos {
	typedef deque <deque <double> > ::iterator record_iterator;
	typedef deque        <double>   ::iterator field_iterator;
	typedef map<int, string> markers;


public:
	struct Trajectory;
	struct Marker;
	const Trajectory pos(const string& filename, const int& Frame);
	map<int, string> column(const string& filename);
	vector<Marker> MarkerList;
	void parsedata(const string& filename);
	const vector<double> get(const string& filename, const int& Frame);
};

#endif
