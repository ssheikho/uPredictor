#ifndef ANNOTATION_UINT64_VALUE_H
#define ANNOTATION_UINT64_VALUE_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Kinect.h>
#elif __linux__
#include <pthread.h>
#include <semaphore.h>
#include "FakeWindowsTypes.h"
#endif


#include "AnnotationValue.h"
//#include "UINT64Value.h"

class AnnotationUINT64Value :
	public AnnotationValue
	//, public UINT64Value
{
public:
	AnnotationUINT64Value(AnnotationType *type);
	virtual ~AnnotationUINT64Value();

	void set(UINT64 val);
	UINT64 get();

	void save(fstream &f);
	void load(fstream &f);

	/*
	//UINT64Value
	void setUINT64Val(UINT64 v);
	UINT64 getUINT64Val();
	*/

protected:
	UINT64 _value;
};

#endif
