#ifndef LAME_COMM_H
#define LAME_COMM_H

class LameComm {
	public:
		LameComm();
		~LameComm();

		virtual void process(char *data) = 0;
};

#endif
