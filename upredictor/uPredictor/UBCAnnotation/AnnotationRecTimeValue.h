#ifndef ANNOTATION_REC_TIME_VALUE_H
#define ANNOTATION_REC_TIME_VALUE_H

#include "AnnotationIntValue.h"

class RecPlayer;

class AnnotationRecTimeValue : public AnnotationIntValue {
public:
	AnnotationRecTimeValue(AnnotationType *type, RecPlayer *rp);
	~AnnotationRecTimeValue();

	RecPlayer *getRP();

protected:
	RecPlayer *_rp;
};

#endif