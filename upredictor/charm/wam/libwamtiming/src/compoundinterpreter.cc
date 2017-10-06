#include "compoundinterpreter.h"
#include "timingutil.h"

#include <iostream>

CompoundInterpreter::CompoundInterpreter(CmdStringInterpreter &csi) :
	_csi(csi) {}
CompoundInterpreter::~CompoundInterpreter() {}

bool CompoundInterpreter::interpret(string inCmd) {
	cout << "COMMAND[-]:	" << inCmd << endl;

	bool retVal = true;
	vector<string> vals = split(inCmd, ';');
	for(int i = 0; (i < vals.size()) && retVal; i++)
		retVal &= _csi.interpret(vals[i]);

	cout << "/COMMAND[" << retVal << "]:	" << inCmd << endl;
	return retVal;
}
