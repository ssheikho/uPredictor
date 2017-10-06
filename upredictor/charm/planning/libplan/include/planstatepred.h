#ifndef PLAN_STATE_PRED_H
#define PLAN_STATE_PRED_H

#include <string>
#include <vector>

using namespace std;

class Problem;

class PlanStatePred {
	public:
		//PlanStatePred(int pred, vector<string> &vals, Problem *problem);
		PlanStatePred(int pred, int nobj, int *obj, int idx, Problem *problem);
		~PlanStatePred();

		void printContents();

		int getPred();
		int getIndex();
		int getObj(int index);

		Problem &getProblem();

		bool equals(int pred, int nobj, int *obj);

		//JWH Yes, I realize I could just check pointers
		bool equals(PlanStatePred &p);

	protected:
		int _pred, _nobj, *_objects, _idx;
		Problem *_problem;
};

#endif
