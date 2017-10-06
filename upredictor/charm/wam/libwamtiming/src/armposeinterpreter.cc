#include "armposeinterpreter.h"
#include "armposer.h"
#include "poslist.h"

ArmPoseInterpreter::ArmPoseInterpreter(ArmPoser &ap, PosList &pl) : _ap(ap),
	_pl(pl) {}

ArmPoseInterpreter::~ArmPoseInterpreter() {}

bool ArmPoseInterpreter::interpret(string inCmd) {
	ArmPose *ap = _pl.getPos(inCmd);

	if(ap)
		_ap.updatePose(ap);

	return ap != NULL;
}
