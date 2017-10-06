#ifndef PARAM_LIST_TABLE_H
#define PARAM_LIST_TABLE_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class Action;
class ActionMap;
class ParamList;
class Problem;

class ParamListTable {
	public:
		ParamListTable(Problem *problem);
		~ParamListTable();

		int size();

		ParamList &getPL(int index);
		ParamList *getPL(string name, vector<string> params);

		void saveTimeData(string fileName);
		void loadTimeData(string fileName);
		void setSaveFile(string fileName);
		void save();
		//void saveTimeFile(string fileName, string timesName);

		vector<ParamList *> getPLForAction(string a);
		vector<ParamList *> getPLForAction(Action *a);
		vector<ParamList *> getPLForAction(int a);

		Problem *getProblem();

	protected:
		class PLTree {
			public:
				PLTree(ParamListTable *plt, ParamList *p, int index = 0);
				~PLTree();
				
				void insert(ParamList *p, int paramNo = 0);
				vector<ParamList *> getAllPL();

				PLTree *get(int obj);
				ParamList *getPL();

				void printChildIDs();

			protected:
				void getAllPL(vector<ParamList *> &v);

				ParamListTable *_plt;
				int _action;
				ParamList *_p;
				map<int, PLTree *> _m;
		};

		void file(ParamList *p);

		Problem *_problem;
		vector<ParamList *> _paramPermutes;
		map<int, PLTree *> _m;
		string _saveFile;
};

#endif
