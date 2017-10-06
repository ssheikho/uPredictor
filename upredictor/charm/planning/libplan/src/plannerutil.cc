#include "plannerutil.h"
#include <cmath>
#include <iostream>

void printIntSet(set<int> in) {
	cout << "(";
	set<int>::iterator i = in.begin();
	while(i != in.end()) { 
		cout << *i;
		i++;
		if(i == in.end())
			cout << ")" << endl;
		else
			cout << ", ";
	}
}

void printIntVect(vector<int> in, bool nelem) {
	if(nelem)
		cout << "[" << in.size() << "]";

	cout << "(";
	vector<int>::iterator i = in.begin();
	while(i != in.end()) { 
		cout << *i;
		i++;
		if(i == in.end())
			cout << ")" << endl;
		else
			cout << ", ";
	}
}

bool fullySubsumedBySmaller(set<int> &test, vector<set<int> > &v) {
	bool retVal = false;
	for(int i = 0; ((i < v.size()) && (!retVal)); i++) {
		bool local = true;
		for(set<int>::iterator j = test.begin(); ((j != test.end()) && (local));
			j++) {
			retVal &= v[i].find(*j) != v[i].end();
		}
		retVal = local && test.size() > v[i].size();
	}
	return retVal;
}

string fixedWidthIntString(int val, int spaces) {
	string retVal = "";
	for(int i = 0; i < spaces; i++) {
		int a = val % 10;
		val -= a;
		val /= 10;
		retVal = itos(a) + retVal;
	}

	if(val != 0) {
		retVal = "";
		for(int i = 0; i < spaces; i++)
			retVal += "X";
	}
			

	return retVal;
}

string itos(int i) {
	string returnVal = "";

	if(i == 0) {
		return "0";
	} else {
		bool neg = i < 0;
		i = abs(i);
		while(i != 0) {
			returnVal =  string("") + ((char)((i % 10) + 48)) + returnVal;
			i -= i % 10;
			i /= 10;
		}
		if(neg)
			returnVal = "-" + returnVal;
		return returnVal;
	}
}

int lameFind(vector<ConcurrentPlanLine *> &v, ConcurrentPlanLine *cpl) {
	int retVal = -1;
	for(int i = 0; ((i < v.size()) && (retVal == -1)); i++) {
		if(v[i] == cpl) retVal = i;
	}
	return retVal;
}

bool hasRepeat(int *v, int n) {
	bool retVal = false;
	
	for(int i = 0; (i < n) && (!retVal); i++) {
		for(int j = 0; (j < n) && (!retVal); j++) {
			if(i != j) retVal = v[i] == v[j];
		}
	}

	return retVal;
}
