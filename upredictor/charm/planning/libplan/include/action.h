#ifndef ACTION_H
#define ACTION_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class ActionPredicate;
class AtomicActionPredicate;
class Domain;
class ObjectTable;
class ParamList;
class ParamListTable;
class PlanState;
class PlanStatePred;
class Problem;

class Action {
	public:
		Action(	string name,
				vector<string> &nameList, vector<string> &typeList,
				Domain &domain, int actionIndex);
		~Action();

		Domain &getDomain();

		string getName();
		string getParam(int index);
		int resolveIndex(string param);
		void setIndex(int index);
		int getIndex();
		int getNParam();

		void printContents();

		AtomicActionPredicate *createActionPredicate(
			string name, vector<string> &parameters);

		void setPrecondition(ActionPredicate *precond, bool maintainPointer);
		void setEffect(ActionPredicate *effect, bool maintainPointer);

		vector<ParamList *> permuteParameters(
			ObjectTable &ot, Problem *problem, ParamListTable *plt);

		bool preconditionsMet(
			map<int, vector<PlanStatePred *> > &pred, ParamList &params);
		bool postConditionsMet(
			map<int, vector<PlanStatePred *> > &pred, ParamList &params);

		void applyEffect(PlanState &to, ParamList &params);

	protected:
		vector<ParamList *> permuteParameters(ObjectTable &ot,
			int *curPermutation, int curParam, Problem *problem,
			ParamListTable *plt);

		string _name;
		Domain &_domain;
		int _nparam, *_types;
		string *_parameters;
		map<string, int> _paramMap;
		ActionPredicate *_precond, *_effect;
		bool _maintainPrecondPointer, _maintainEffectPointer;
		int _actionIndex;
};

#endif
