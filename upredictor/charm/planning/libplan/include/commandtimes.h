#ifndef COMMAND_TIMES_H
#define COMMAND_TIMES_H

class ParamList;
class ParamListTable;

class CommandTimes {
	public:
		CommandTimes(ParamListTable &plt);
		CommandTimes();

	protected:
		ParamListTable &_plt;
};

#endif
