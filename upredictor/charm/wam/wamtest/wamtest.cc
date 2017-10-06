#include <poslist.h>
#include <armpose.h>

#include <barrett/math.h> 
#include <barrett/units.h>
#include <barrett/systems.h>

#include <iostream>

//using namespace barrett;
using namespace std;

int main(int argc, char **argv) {
	cout << "Opening Position File:	" << argv[1] << endl;
	PosList<7ul> testlist(argv[1]);
	ArmPose<7ul> * testPose = testlist.getPos("rhole2_grasp");
	//check that ArmPose has proper joint angle data
	testPose->printDest();
	return 0;
}
