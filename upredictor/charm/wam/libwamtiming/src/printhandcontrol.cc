#include "printhandcontrol.h"

#include <iostream>

using namespace std;

PrintHandControl::PrintHandControl() {}
PrintHandControl::~PrintHandControl() {}

void PrintHandControl::open(bool blocking) {
	cout << "Open Hand:	" << blocking << endl;
}

void PrintHandControl::close(bool blocking) {
	cout << "Close Hand:	" << blocking << endl;
}

