#ifndef ACTION_EXECUTOR_H
#define ACTION_EXECUTOR_H

class ParamList;

class ActionExecutor {
	public:
		ActionExecutor();
		~ActionExecutor();
	
		virtual void execute(ParamList *pl) = 0;
		
};

#endif
