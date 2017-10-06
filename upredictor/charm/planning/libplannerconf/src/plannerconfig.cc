#include "plannerconfig.h"

#include <fstream>
#include <iostream>

using namespace std;

PlannerConfig::PlannerConfig() {}
PlannerConfig::~PlannerConfig() {}

void PlannerConfig::load(string filename) {
	ifstream f(filename.c_str());
	f >> _domainFile;
	f >> _problemFile;
	f >> _actorFile;
	f >> _stateTimeFile;

	f >> _domainName;
	f >> _problemName;

	f >> _loadTimes;
	f >> _saveTimes;
}

string PlannerConfig::getDomainFile() {
	return _domainFile;
}

string PlannerConfig::getProblemFile() {
	return _problemFile;
}

string PlannerConfig::getActorFile() {
	return _actorFile;
}

string PlannerConfig::getTimeFile() {
	return _stateTimeFile;
}

string PlannerConfig::getDomainName() {
	return _domainName;
}

string PlannerConfig::getProblemName() {
	return _problemName;
}

bool PlannerConfig::loadTimes() {
	return _loadTimes;
}

bool PlannerConfig::saveTimes() {
	return _saveTimes;
}

void PlannerConfig::printContents() {
	cout << "DomainFile:	" << _domainFile << endl;
	cout << "ProblemFile:	" << _problemFile << endl;
	cout << "ActorFile:	" << _actorFile << endl;
	cout << "stateTimeFile:	" << _stateTimeFile << endl;

	cout << "Domain:	" << _actorFile << endl;
	cout << "Problem:	" << _stateTimeFile << endl;

	cout << "loadTimes:	" << loadTimes() << endl;
	cout << "saveTimes:	" << saveTimes() << endl;
}
