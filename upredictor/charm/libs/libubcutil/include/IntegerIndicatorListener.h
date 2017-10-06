#ifndef INTEGER_INDICATOR_LISTENER_H
#define INTEGER_INDICATOR_LISTENER_H

class IntegerIndicator;

class IntegerIndicatorListener {
public:
	virtual void updateII(IntegerIndicator *ii) = 0;
};

#endif