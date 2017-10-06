/*
The poslist class is primarily a mapping between armpose objects
and strings which describe each pose.
*/

#include "poslist.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h> 
#include <sstream>

using namespace std;

PosList::PosList(int dof) : _dof(dof) {}

PosList::~PosList() {}

void PosList::clear() {
	for(int i = 0; i < _posList.size(); i++) {
		delete _posList[i];
	}
	_posList.clear();
	_posMap.clear();
}

void PosList::load(string filename) {
	string line;
	ifstream fs(filename.c_str());

	if(fs.is_open()){
		while(getline (fs,line)) {
			//cout << "PosList::load:	" << line << endl;
			// first string goes to _posMap's key
			// remainder of the line goes to _posMap's value
			istringstream ss(line);
			string buffer;
			string posKey;
			vector <string> record;
			float angleSet[_dof]; 
			while (ss){
				getline(ss,buffer,',');
				record.push_back(buffer);
			}
			posKey = record[0];
			for (int i=1; i<8; i++){
				angleSet[i-1]=atof(record[i].c_str());
				//cout << angleSet[i-1] << endl;				
			}
			new DefaultArmPose(this, posKey, angleSet, _dof);
			//cout << "Made an ArmPose!" << endl;
		}
		fs.close();	
	} else {
		cout << "Unable to open file" << endl;
	}
}

void PosList::save(string filename) {
	cout << "PosList::save:	" << filename << endl;
	string line;
	ofstream fs(filename.c_str());

	if(fs.is_open()){
		for(int i = 0; i < rows(); i++) {
			ArmPose *ap = getPos(i);
			fs << ap->getName();
			fs << ",";
			for(int j = 0; j < ap->getNAngs(); j++) {
				fs << ap->getAng(j);
				if(j < (ap->getNAngs() - 1))
					fs << ",";
			}
			fs << endl;
		}
		fs.close();	
	} else {
		cout << "Unable to open file" << endl;
	}
}

ArmPose *PosList::getPos(int index) {
	return _posList[index];
}

ArmPose *PosList::getPos(string posName) {
	return _posList[_posMap[posName]];
}

void PosList::addPose(ArmPose *ap) {
	_posMap[ap->getName()] = _posList.size();
	_posList.push_back(ap);
}

int PosList::rows() {
	return _posList.size();
}

int PosList::getDOF() {
	return _dof;
}

void PosList::printContents() {
	for(int i = 0; i < _posList.size(); i++) {
		_posList[i]->printDest();
	}
}

/*
//Because C++ templates are wonky, you either have to declare all of your
//	methods inline, or declare them for every type you intend to pass to the
//	template.  I did the latter.
template PosList<4ul>::PosList(string filename);
template PosList<7ul>::PosList(string filename);

template PosList<4ul>::~PosList();
template PosList<7ul>::~PosList();

template ArmPose<4ul> * PosList<4ul>::getPos(string posName);
template ArmPose<7ul> * PosList<7ul>::getPos(string posName);
*/
