#ifndef ARM_POSE_INTERPRETER_H
#define ARM_POSE_INTERPRETER_H

#include "cmdstringinterpreter.h"

class ArmPoser;
class PosList;

class ArmPoseInterpreter : public CmdStringInterpreter {
	public:
		ArmPoseInterpreter(ArmPoser &ap, PosList &pl);
		~ArmPoseInterpreter();

		bool interpret(string inCmd);

	protected:
		ArmPoser &_ap;
		PosList &_pl;
};

#endif
