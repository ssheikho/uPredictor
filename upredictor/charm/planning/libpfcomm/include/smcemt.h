#ifndef SMC_EMT_H
#define SMC_EMC_H

#include <map>
#include <string>
#include <vector>

using namespace std;

//SMC Event Model Table

class ParamList;
class ParamListTable;
class PFPerson;
class SMCConnection;
class SMCEventModel;
class WorldModel;

class SMCEMT {
	public:
		SMCEMT(ParamListTable &plt, WorldModel *wm, SMCConnection &smcc,
			PFPerson &person, bool liveFire);
		~SMCEMT();

		SMCEventModel *getEM(ParamList *pl);

		void load(string filename);

	protected:
		ParamListTable &_plt;
		WorldModel *_wm;
		SMCConnection &_smcc;
		PFPerson &_person;
		bool _liveFire;

		vector<SMCEventModel *> _v;
		map<int, int> _m;
};

#endif
