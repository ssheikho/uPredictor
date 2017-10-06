#ifndef PRINT_HAND_CONTROL_H
#define PRINT_HAND_CONTROL_H

#include "handcontrol.h"

class PrintHandControl : public HandControl {
	public:
		PrintHandControl();
		~PrintHandControl();

		void open(bool blocking = true);
		void close(bool blocking = true);
};

#endif
