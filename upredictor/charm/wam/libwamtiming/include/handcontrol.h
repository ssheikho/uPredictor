#ifndef HAND_CONTROL_H
#define HAND_CONTROL_H

class HandControl {
	public:
		HandControl();
		~HandControl();

		virtual void open(bool blocking = true) = 0;
		virtual void close(bool blocking = true) = 0;
};

#endif
