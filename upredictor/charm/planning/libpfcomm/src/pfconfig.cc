#include "pfconfig.h"

#include <fstream>
#include <iostream>

using namespace std;

PFConfig::PFConfig() {}
PFConfig::~PFConfig() {}

void PFConfig::load(string filename) {
	ifstream f(filename.c_str());
	f >> _domainFile;
	f >> _problemFile;
	f >> _concurrencyFile;
	f >> _actorFile;
	f >> _stateEMTFile;
	f >> _stateTimeFile;

	f >> _smcServerAddress;
	f >> _smcName;

	f >> _smcVerbosity;
	f >> _connectToSMC;
	f >> _loadTimes;
	f >> _saveTimes;
}

string PFConfig::getDomainFile() {
	return _domainFile;
}

string PFConfig::getProblemFile() {
	return _problemFile;
}

string PFConfig::getConcurrencyFile() {
	return _concurrencyFile;
}

string PFConfig::getActorFile() {
	return _actorFile;
}

string PFConfig::getEMTFile() {
	return _stateEMTFile;
}

string PFConfig::getTimeFile() {
	return _stateTimeFile;
}

string PFConfig::getSMCServerAddr() {
	return _smcServerAddress;
}

string PFConfig::getSMCClientName() {
	return _smcName;
}

int PFConfig::getSMCVerbosity() {
	return _smcVerbosity;
}

bool PFConfig::connectToSMC() {
	return _connectToSMC;
}

bool PFConfig::loadTimes() {
	return _loadTimes;
}

bool PFConfig::saveTimes() {
	return _saveTimes;
}

void PFConfig::printContents() {
	cout << "DomainFile:	" << _domainFile << endl;
	cout << "ProblemFile:	" << _problemFile << endl;
	cout << "ConcurrencyFile:	" << _concurrencyFile << endl;
	cout << "ActorFile:	" << _actorFile << endl;
	cout << "StateEMTFile:	" << _stateEMTFile << endl;
	cout << "stateTimeFile:	" << _stateTimeFile << endl;

	cout << "ConnectToSMC:	" << connectToSMC() << endl;

	cout << "loadTimes:	" << loadTimes() << endl;
	cout << "saveTimes:	" << saveTimes() << endl;
}
