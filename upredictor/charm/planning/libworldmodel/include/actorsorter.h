#ifndef ACTOR_SORTER_H
#define ACTOR_SORTER_H

#include <map>
#include <string>
#include <vector>

class ActorEventLine;
class ActorPlan;
class ConcurrentPlan;
class ParamListTable;
class Plan;
class WorldModel;

using namespace std;

class ActorSorter {
	public:
		ActorSorter();
		~ActorSorter();

		ActorPlan *processPlan(Plan *p, WorldModel &wm);
		//ActorPlan *processConcurrentPlan(ConcurrentPlan *cp);

		void addActor(string name);
		void addAction(string action, string actor);

		void processPLT(ParamListTable *plt);

		void printContents();

	protected:
		//void processConcurrentPlanTwo(ConcurrentPlan *cp, ActorPlan *ap);

		ActorPlan *generateAP(Plan *p);
		//ActorPlan *generateAP(ConcurrentPlan *cp);

		int _nActors;
		ParamListTable *_plt;

		map<string, int> _actorMap;
		map<int, string> _actorReverseMap;
		map<string, int> _actionToActor;
		map<int, int> _plToActor;
};

/*
		void loadPlugfest();

		//ActorPlan *processConcurrentPlan(ConcurrentPlan *cp);
		//vector<ActorEventLine *> _actors;
*/

#endif
