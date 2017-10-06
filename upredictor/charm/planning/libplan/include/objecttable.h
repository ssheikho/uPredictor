#ifndef OBJECT_TABLE_H
#define OBJECT_TABLE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class Problem;

class ObjectTable {
	public:
		ObjectTable(Problem *problem);
		~ObjectTable();

		void populateObjects(vector<string> &ids, string type);
		int getObjectID(string name);
		string getObjectName(int id);

		void printContents();

		bool isA(int object, int type);
		vector<int> &getAllOfType(int type);
		int findFirst(int type);
		int findNext(int atOrAfter, int type);
		
		int nObj();	//JWH	We assume that every ID is taken.

	protected:
		Problem *_problem;
		map<int, int> _isA;
		map<int, vector<int> > _byType;
		vector<string> _objectNames;
		map<string, int> _objectIDs;
		int _objectCtr;
		
};

#endif
