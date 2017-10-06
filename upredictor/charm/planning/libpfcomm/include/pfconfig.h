#ifndef PF_CONFIG_H
#define PF_CONFIG_H

#include <string>

using namespace std;

class PFConfig {
	public:
		PFConfig();
		~PFConfig();

		void load(string filename);

		string getDomainFile();
		string getProblemFile();
		string getConcurrencyFile();
		string getActorFile();
		string getEMTFile();
		string getTimeFile();

		string getSMCServerAddr();
		string getSMCClientName();
		int getSMCVerbosity();
		bool connectToSMC();
		bool loadTimes();
		bool saveTimes();

		void printContents();

	protected:
		string	_domainFile, _problemFile, _concurrencyFile, _actorFile,
				_stateEMTFile, _stateTimeFile, _smcServerAddress, _smcName;
		int _smcVerbosity, _connectToSMC, _loadTimes, _saveTimes;
		//mParams.mServerAddress, mParams.mName, mParams.mSMCModule, 5, mParams.mVerboseLevel-1
};

#endif
