#ifndef NO_CONCUR_TABLE_H
#define NO_CONCUR_TABLE_H

#include <set>
#include <map>

using namespace std;

//JWH	Another thought is to add "exclusive-access" to some actions over
//		some of their objects.  This would allow, for instance, to say that
//		nothing else can affect a screw while a gripper is holding it.
//		For now, however, this will suffice.

class NoConcurTable {
	public:
		NoConcurTable();
		~NoConcurTable();

		void add(int actionOne, int actionTwo);
		bool isNoConcur(int actionOne, int actionTwo);
;
	protected:
		map<int, set<int> > _m;
};

#endif
