#ifndef TYPE_RECIPIENT_H
#define TYPE_RECIPIENT_H

template<typename T> class TypeRecipient {
public:
	virtual void processType(T t) = 0;
	virtual void onStartup() {};
};

#endif
