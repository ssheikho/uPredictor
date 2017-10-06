#ifndef ACTOR_PLAN_H
#define ACTOR_PLAN_H

#include <map>
#include <vector>

using namespace std;

class ActorEventLine;
class ActorPlan;
class ConcurrentPlan;
class ParamListTable;
class Plan;
class WorldModel;

class ActorPlan {
	public:
		ActorPlan(Plan *p);
		//ActorPlan(ConcurrentPlan *cp);
		~ActorPlan();

		void addAEL(int index, ActorEventLine *ael);
		ActorEventLine *getAEL(int index);
		int getNActors();

		//void compressPlan(WorldModel &wm);
		//bool compressNextSteps(WorldModel &wm, int maxSteps);
		//bool compressNullSteps(WorldModel &wm, int maxSteps);
		bool allNullAt(int index);

		void printContents();

		int getNSteps();
		void setNSteps(int nSteps);

		bool equals(ActorPlan *ap);

		int nextKeyFrame(int startAt);

		Plan *getPlan();

	protected:
		Plan *_p;
		//ConcurrentPlan *_cp;
		map<int, ActorEventLine *> _actors;
		vector <PlanState *> _planStates;
		int _nSteps;
};

#endif
