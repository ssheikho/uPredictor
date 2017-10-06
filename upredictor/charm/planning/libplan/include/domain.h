#ifndef DOMAIN_H
#define DOMAIN_H

#include "actionmap.h"
#include "noconcurtable.h"
#include "predicatemap.h"
#include "typemap.h"

#include <map>
#include <string>

using namespace std;

class Problem;

class Domain {
	public:
		Domain();
		Domain(string name);
		~Domain();

		void setName(string name);
		string getName();

		void printContents();

		TypeMap &types();
		PredicateMap &predicates();
		ActionMap &actions();
		NoConcurTable &NCT();

		Problem *newProblem(string name);
		Problem *getProblem(string name);

	protected:
		string _name;
		TypeMap _types;
		PredicateMap *_predicates;
		ActionMap *_actions;
		NoConcurTable _nct;

		map<string, Problem *> _m;
};

#endif
