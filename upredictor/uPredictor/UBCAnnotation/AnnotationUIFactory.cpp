#include "AnnotationUIFactory.h"
#include "AnnotationEnumUI.h"
#include "AnnotationIntValue.h"
#include "AnnotationType.h"
#include "AnnotationValue.h"
#include "AnnotationUINT64Value.h"
#include "AnnotationUtil.h"
//#include "IntValueArray.h"
//#include "IntValueArrayMultiplexer.h"
#include "SimpleLabeledSlider.h"
#include "KinectInterface.h"
//#include "KinectPlayer.h"
//#include "UINT64ListCB.h"

AnnotationUIFactory::AnnotationUIFactory() {}//KinectPlayer &kp) : _kp(kp) {}
AnnotationUIFactory::~AnnotationUIFactory() {}

LayoutElement *AnnotationUIFactory::createUI(AnnotationValue *av,
	LayoutContainer *parent) {
	LayoutElement *le = NULL;

	AnnotationType *at = av->getType();
	AnnotationTypes type = at->getType();

	switch (type) {
	case AnnotationTypes::enumerated:
		le = new AnnotationEnumUI(
			dynamic_cast<AnnotationIntValue *>(av), parent);
		break;
	case AnnotationTypes::trackId:
		/*
		le = new UINT64ListCB(
			&_kp.getKI().getTIDM(),
			dynamic_cast<AnnotationUINT64Value *>(av),
			parent, 100, 25);
		*/
		break;
	case AnnotationTypes::recTime: {
		/*
		IntValueArrayMultiplexer *ivam = new IntValueArrayMultiplexer();
		ivam->addIVA(&_kp, false, false);
		ivam->addIVA(
			dynamic_cast<IntValueArray *>(
			dynamic_cast<AnnotationIntValue *>(av)), true, true);
		le = new SimpleLabeledSlider(ivam, 0, true, parent, 500, 25);
		*/
	}
		break;
	}

	return le;
}