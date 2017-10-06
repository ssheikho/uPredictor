#include "paramlisttable.h"
#include "action.h"
#include "actionmap.h"
#include "domain.h"
#include "paramlist.h"
#include "problem.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

ParamListTable::ParamListTable(Problem *problem) : _problem(problem),
	_saveFile("") {
	//JWH Create all interesting permutations of problem variables as parameters
	//	of the relevant actions
	ActionMap &actions = _problem->getDomain().actions();
	for(int i = 0; i < actions.nActions(); i++) {
		Action *curAction = actions.getAction(i);
		//cout << "ParamListTable::ParamListTable:	" << curAction->getName() <<
		//	endl;
		vector<ParamList *> p =
			curAction->permuteParameters(problem->getObjectTable(), _problem,
			this);
		_paramPermutes.insert(_paramPermutes.end(), p.begin(), p.end());
	}

	for(int i = 0; i < _paramPermutes.size(); i++) {
		_paramPermutes[i]->setIndex(i);
		file(_paramPermutes[i]);
	}
}

ParamListTable::~ParamListTable() {
	for(int i = 0; i < _paramPermutes.size(); i++)
		delete _paramPermutes[i];
}

void ParamListTable::setSaveFile(string fileName) {
	_saveFile = fileName;
}

void ParamListTable::save() {
	cout << "ParamListTable::save():	" << _saveFile << endl;
	saveTimeData(_saveFile);
}

int ParamListTable::size() {
	return _paramPermutes.size();
}

ParamList &ParamListTable::getPL(int index) {
	return *_paramPermutes[index];
}

ParamList *ParamListTable::getPL(string name, vector<string> params) {
	//cout << "ParamListTable::getPL:	" << name << endl;
	ActionMap &am = _problem->getDomain().actions();
	ObjectTable &ot = _problem->getObjectTable();
	int act = am.resolveIndex(name);

	ParamListTable::PLTree *pltree = _m[act];

	pltree->printChildIDs();

	for(int i = 0; i < params.size(); i++) {
		int objId = ot.getObjectID(params[i]);
		pltree = pltree->get(objId);
	}

	ParamList *pl = pltree->getPL();

	return pl;
}

/*
void ParamListTable::saveTimeFile(string fileName, string timesName) {
	Domain &domain = _problem->getDomain();

	ofstream o(fileName.c_str());
	o.precision(4);
	o << std::fixed << endl;

	o << "(define" << endl;
	o << "	(times " << timesName << ")" << endl;
	o << "	(:domain " << domain.getName() << ")" << endl;
	o << "	(:problem " << _problem->getName() << ")" << endl;
	o << "	(:times" << endl;

	for(int i = 0; i < _paramPermutes.size(); i++) {
		_paramPermutes[i]->save(o);
	}

	o	<< "	)" << endl
		<< ")" << endl;
	
	o.flush();
	o.close();
}
*/

void ParamListTable::saveTimeData(string fileName) {
	ofstream outfile(fileName.c_str(), ofstream::binary);

	int nElem = _paramPermutes.size();
	outfile.write((char *)&nElem, sizeof(nElem));

	for(int i = 0; i < nElem; i++) {
		_paramPermutes[i]->getTV().saveTimeData(outfile);
	}
		
	outfile.flush();
	outfile.close();
}

void ParamListTable::loadTimeData(string fileName) {
	ifstream infile(fileName.c_str(), ofstream::binary);

	int nElem = 0;//_paramPermutes.size();
	infile.read((char *)&nElem, sizeof(nElem));

	for(int i = 0; i < nElem; i++) {
		_paramPermutes[i]->getTV().loadTimeData(infile);
	}
		
	infile.close();
}

vector<ParamList *> ParamListTable::getPLForAction(string a) {
	getPLForAction(_problem->getDomain().actions().resolveIndex(a));
}

vector<ParamList *> ParamListTable::getPLForAction(Action *a) {
	return getPLForAction(a->getIndex());
}

vector<ParamList *> ParamListTable::getPLForAction(int a) {
	return _m[a]->getAllPL();
}

void ParamListTable::file(ParamList *p) {
	int act = p->getAction().getIndex();
	if(_m.find(act) == _m.end()) {
		_m[act] = new PLTree(this, p);
	} else {
		_m[act]->insert(p);
	}
}

Problem *ParamListTable::getProblem() {
	return _problem;
}

ParamListTable::PLTree::PLTree(ParamListTable *plt, ParamList *p, int index) :
	_plt(plt), _action(p->getAction().getIndex()), _p(NULL) {
	insert(p, index);
}

ParamListTable::PLTree::~PLTree() {}

void ParamListTable::PLTree::insert(ParamList *p, int paramNo) {
	if(paramNo == p->getNVals()) {
		_p = p;
	} else {
		int obj = p->getParamObj(paramNo);
		if(_m.find(obj) == _m.end()) {
			_m[obj] = new PLTree(_plt, p, paramNo + 1);
		} else {
			_m[obj]->insert(p, paramNo + 1);
		}
	}
}

vector<ParamList *> ParamListTable::PLTree::getAllPL() {
	vector<ParamList *> retVal;
	getAllPL(retVal);
	return retVal;
}

void ParamListTable::PLTree::getAllPL(vector<ParamList *> &v) {
	if(_m.size())
		for(map<int, PLTree *>::iterator i = _m.begin(); i != _m.end(); i++)
			i->second->getAllPL(v);
	else
		v.push_back(_p);
}

ParamListTable::PLTree *ParamListTable::PLTree::get(int obj) {
	//cout << "ParamListTable::PLTree::get:	" << obj << endl;
	return _m[obj];
}

ParamList *ParamListTable::PLTree::getPL() {
	return _p;
}

void ParamListTable::PLTree::printChildIDs() {
	cout << "ParamListTable::PLTree::printChildIDs():	" << _m.size() << endl;
	for(map<int, PLTree *>::iterator iter = _m.begin(); iter != _m.end();
		iter++) {
		cout << "CHILD:	" << iter->first << endl;
	}
}
