#ifndef PLANNER_CONFIG_H
#define PLANNER_CONFIG_H

#include <string>

using namespace std;

class PlannerConfig {
	public:
		PlannerConfig();
		~PlannerConfig();

		void load(string filename);

		string getDomainFile();
		string getProblemFile();
		string getActorFile();
		string getTimeFile();

		string getDomainName();
		string getProblemName();

		bool loadTimes();
		bool saveTimes();

		void printContents();

	protected:
		string	_domainFile, _problemFile, _actorFile, _stateTimeFile,
			_domainName, _problemName;
		int _smcVerbosity, _connectToSMC, _loadTimes, _saveTimes;
		//mParams.mServerAddress, mParams.mName, mParams.mSMCModule, 5, mParams.mVerboseLevel-1
};

#endif
