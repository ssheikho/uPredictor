
#include "csv.h"
#include <fstream>
#include <iostream>
#include "ViconFunctions.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char **argv) {
	ifstream f(argv[1]);
	
 	
	ViconData *vd = loadVD(f);

	f.close();

	return 0;
}
