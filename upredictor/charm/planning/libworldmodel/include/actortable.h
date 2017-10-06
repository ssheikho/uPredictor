#ifndef ACTOR_TABLE_H
#define ACTOR_TABLE_H

#include "actiontoactor.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class ActionMap;
class Actor;
class ActorFactory;
class Domain;
class WorldModel;

class ActorTable {
	public:
		ActorTable(ActionMap &am, ActorFactory &af);
		~ActorTable();

		void setName(string name);

		Actor *getActor(string name, string type, string conf);
		Actor *getActor(int index);

		void load(string fileName);
		void setDomain(Domain *domain);

		ActionToActor &getATA();

	protected:
		ActorFactory &_af;

		string _name;
		Domain *_domain;

		ActionToActor _ata;

		vector<Actor *> _v;
		map<string, int> _m;
};

#endif
