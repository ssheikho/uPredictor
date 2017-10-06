#ifndef MY_CLASS_H
#define MY_CLASS_H

#include "MyParentClass.h"

class MyClass : public MyParentClass {
public:
	MyClass();
	~MyClass();

	void yellAtFamily();

protected:
	void doYourClassThing();

};

#endif