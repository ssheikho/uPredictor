#include "ViconFunctions.h"

#include <cstring>
#include <iostream>

using namespace std;

ViconData *loadVD(ifstream &f) {
	ViconData *vd = new ViconData();

	string line;
	getline(f, line);

	while(!f.eof() && (strncmp(line.c_str(), "Trajectories", 12) != 0))
		getline(f, line);

	string numberLine;
	string labelLine;
	string axislLine;
	string unitslLine;
	getline(f, numberLine);
	getline(f, labelLine);
	getline(f, axislLine);
	getline(f, unitslLine);

	
	//cout << numberLine << endl;
	//cout << labelLine << endl;
	//cout << axislLine << endl;
	//cout << unitslLine << endl;

	vd->getVT().setLabels(labelLine);
	

	//while(!f.eof()) {
	//	getline(f, line);
	//	cout << line << endl;
	//}

	return vd;
}
