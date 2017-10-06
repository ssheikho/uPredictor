#include "wamhandcontrol.h"

WAMHandControl::WAMHandControl(Hand *hand) : _hand(hand) {}
WAMHandControl::~WAMHandControl() {}

void WAMHandControl::open(bool blocking) {
	_hand->open(Hand::GRASP, blocking);
}

void WAMHandControl::close(bool blocking) {
	_hand->close(Hand::WHOLE_HAND, blocking);
}
