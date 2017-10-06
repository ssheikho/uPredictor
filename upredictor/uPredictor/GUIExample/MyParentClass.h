#ifndef MY_PARENT_CLASS_H
#define MY_PARENT_CLASS_H

class MyParentClass {
public:
	MyParentClass();
	~MyParentClass();

	virtual void yellAtFamily() = 0;

protected:
	void beAParent();
};

#endif