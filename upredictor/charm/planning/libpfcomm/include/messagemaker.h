#include <string>
#include "paramlist.h"

using namespace std;

//class ParamList;

class MessageMaker {
	public:
		MessageMaker(ParamList &pl);
		~MessageMaker();
		
		string getMessage();

		void printContents(bool cr = true);

		//Actor *getActor(ActionToActor &ata, string name, int id, string type,
		//	string configfile); 

	protected:
		ParamList &_pl;
};

