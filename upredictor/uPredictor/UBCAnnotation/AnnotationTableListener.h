#ifndef ANNOTATION_TABLE_LISTENER_H
#define ANNOTATION_TABLE_LISTENER_H

class AnnotationObject;
class AnnotationTable;

class AnnotationTableListener {
public:
	virtual void addAnnotationObject(AnnotationTable *at, AnnotationObject *ao) = 0;
	virtual void clearAnnotationObjects(AnnotationTable *at) = 0;
};

#endif