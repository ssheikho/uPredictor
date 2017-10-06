#ifndef PREDICATE_MAP_H
#define PREDICATE_MAP_H

#include "predicate.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class Domain;

class PredicateMap {
	public:
		PredicateMap(Domain &domain);
		~PredicateMap();

		void insert(string name, vector<string> &parameters,
			vector<string> &types);
		Predicate &getPred(int index);
		int size();

		string getName(int i);
		int getIndex(string name);

		void printContents();

	protected:

		Domain &_domain;
		vector<Predicate *> _v;
		map<string, int> _m;
		int _ctr;
};

#endif
