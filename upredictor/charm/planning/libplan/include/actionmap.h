#ifndef ACTION_MAP_H
#define ACTION_MAP_H

#include "action.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class Domain;

class ActionMap {
	public:
		ActionMap(Domain &domain);
		~ActionMap();

		Action *insert(string name,
			vector<string> &nameList, vector<string> &typeList);

		int resolveIndex(string name);
		Action *getAction(int index);
		int nActions();

		void printContents();

		Action *combineTwoActions();

	protected:
		Domain &_domain;

		vector<Action *> _v;
		map<string, int> _m;
		int _ctr;
};

#endif
