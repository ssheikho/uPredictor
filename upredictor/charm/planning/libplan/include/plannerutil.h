#ifndef PLANNER_UTIL_H
#define PLANNER_UTIL_H

#include <set>
#include <string>
#include <vector>

using namespace std;

class ConcurrentPlanLine;

void printIntSet(set<int> in);
void printIntVect(vector<int> in, bool nelem);
bool fullySubsumedBySmaller(set<int> &test, vector<set<int> > &v);
string fixedWidthIntString(int val, int spaces = 3);
string itos(int i);
int lameFind(vector<ConcurrentPlanLine *> &v, ConcurrentPlanLine *cpl);
bool hasRepeat(int *v, int n);

#endif
