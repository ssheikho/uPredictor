#ifndef CMD_STRING_INTERPRETER_H
#define CMD_STRING_INTERPRETER_H

#include <string>

using namespace std;

class CmdStringInterpreter {
	public:
		CmdStringInterpreter();
		~CmdStringInterpreter();

		virtual bool interpret(string inCmd) = 0;
		
};

#endif
