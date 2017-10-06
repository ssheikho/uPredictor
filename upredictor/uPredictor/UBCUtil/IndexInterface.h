#ifndef INDEX_INTERFACE_H
#define INDEX_INTERFACE_H

template<typename T> class IndexInterface {
public:
	virtual void rename(T from, T to) = 0;
};

#endif