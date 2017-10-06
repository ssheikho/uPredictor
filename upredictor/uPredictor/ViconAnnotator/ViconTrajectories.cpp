#include "ViconTrajectories.h"

#include <iostream>
#include <sstream>

using namespace std;

ViconTrajectories::ViconTrajectories() {}
ViconTrajectories::~ViconTrajectories() {}

void ViconTrajectories::setLabels(string labelsLine) {
	istringstream labelStream(labelsLine);
	string token;
	int tokenNumber = 0;
	while(getline(labelStream, token, ',')) {
		//cout << "[" << tokenNumber << "]	" << token << endl;
		if(token.length()) _nci.insert(token, tokenNumber);
		tokenNumber++;
	}

	_nci.printTable();
}

NameCrossIndex &ViconTrajectories::getNCI() {
	return _nci;
}
