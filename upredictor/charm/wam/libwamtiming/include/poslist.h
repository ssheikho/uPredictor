/*
The poslist class is primarily a mapping between armpose objects
and strings which describe each pose.
*/

#ifndef POS_LIST_H
#define POS_LIST_H

#include "defaultarmpose.h"

#include <map>
#include <string>
#include <vector>
/*
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h> 
#include <sstream>
*/
using namespace std;

//class ArmPose;

class PosList {
	public:
		PosList(int dof);
		~PosList();

		ArmPose *getPos(int index);
		ArmPose *getPos(string posName);

		void printContents();

		void clear();
		void load(string filename);
		void save(string filename);

		void addPose(ArmPose *ap);
		int rows();
		int getDOF();

	protected:
		int _dof;
		map<string, int> _posMap;
		vector<ArmPose *> _posList;
};

#endif
