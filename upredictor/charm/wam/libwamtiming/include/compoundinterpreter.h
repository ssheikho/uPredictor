#ifndef COMPOUND_INTERPRETER_H
#define COMPOUND_INTERPRETER_H

#include "cmdstringinterpreter.h"

class CompoundInterpreter : public CmdStringInterpreter {
	public:
		CompoundInterpreter(CmdStringInterpreter &csi);
		~CompoundInterpreter();

		bool interpret(string inCmd);

	protected:
		CmdStringInterpreter &_csi;
};

#endif
