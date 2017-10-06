#ifndef ACTOR_H
#define ACTOR_H

#include <string>

using namespace std;

class ActionToActor;
class ParamList;
class WorldModel;

class Actor {
	public:
		Actor(string name, int id, ActionToActor &ata, WorldModel &wm);
		~Actor();

		string getName();
		int getIndex();

		void registerAction(string action);
	
		virtual void execute(ParamList *pl) = 0;
		virtual void configure() = 0;

	protected:
		void notifyParamList(ParamList *pl);

		string _name;
		int _id;
		ActionToActor &_ata;
		WorldModel &_wm;
};

#endif
