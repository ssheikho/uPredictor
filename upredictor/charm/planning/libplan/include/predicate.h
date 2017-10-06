#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>

using namespace std;

class Domain;

class Predicate {
	public:
		Predicate(string name,
			vector<string> &parameters, vector<string> &types,
			Domain &domain, int index);
		~Predicate();

		int getIndex();
		int getNParam();
		int getParamType(int index);

		string getName();

		void printContents();

	protected:
		string _name;
		Domain &_domain;
		int _nparam, *_types, _index;
		string *_parameters;
};

#endif
