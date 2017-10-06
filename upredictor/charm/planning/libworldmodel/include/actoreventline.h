#ifndef ACTOR_EVENT_LINE_H
#define ACTOR_EVENT_LINE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class ActorPlan;
class ParamList;
class PlanState;
class Problem;

class ActorEventLine {
	public:
		ActorEventLine(string name);
		~ActorEventLine();

		void add(ParamList *pl);

		ParamList *getPL(int index);
		bool actionAtTimeSlot(int index);

		void printContents();
		void printLineAt(int index);

		int getNTimeSteps();

		bool equals(ActorEventLine *ap);

		int nextNullStart(int startAt);
		int nextNullEnd(int startAt);

	protected:
		void printBrackets(int start, int swap, int end);

		string _name;
		vector<ParamList *> _timeSlots;
		vector<double> _times;
};

#endif
