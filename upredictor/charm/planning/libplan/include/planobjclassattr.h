#ifndef PLAN_OBJ_CLASS_ATTR_H
#define PLAN_OBJ_CLASS_ATTR_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class PlanObjClassAttr {
	public:
		PlanObjClassAttr();
		~PlanObjClassAttr();

		void addVal(string val);
		int getNumeric(string val);
		int numVals();

	protected:
		map<string, int> _vals;
};

#endif 
