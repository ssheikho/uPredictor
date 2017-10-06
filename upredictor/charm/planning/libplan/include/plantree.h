#ifndef PLAN_TREE_H
#define PLAN_TREE_H

#include <map>
#include <vector>

using namespace std;

class ParamListTable;
class Plan;
class PlanningGraph;

class PlanTree {
	public:
		PlanTree(int paramList, int state, PlanTree *parent,
			ParamListTable &plt, PlanningGraph *pg);
		~PlanTree();

		void insert(Plan &p, int atActionNumber);

		void printPlanToHere(bool end, bool mnemoic);

		map<int, PlanTree *> &getChildren();
		PlanTree *getChildByIndex(int index);
		int getNumChildNodes();
		

		int getParamList();
		int getState();

		int idLabelTree();
		int getID();

	protected:
		bool canDoChild(PlanTree *pt);
		int idLabelTree(int startAt);

		int _paramList, _state, _id;
			//JWH	State if *after* _paramLists's action.
		PlanTree *_parent;
		ParamListTable &_plt;
		PlanningGraph *_pg;
		map<int, PlanTree *> _m;
		vector<PlanTree *> _v;
};

#endif
