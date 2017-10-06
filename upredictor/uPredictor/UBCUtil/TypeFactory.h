#ifndef TYPE_FACTORY_H
#define TYPE_FACTORY_H

template<typename T> class TypeFactory {
public:
	virtual T *getInstance() = 0;
};

#endif