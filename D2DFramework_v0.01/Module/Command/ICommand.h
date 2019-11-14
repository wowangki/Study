#pragma once

class IState;
class ICommand {
public:
	virtual ~ICommand() {}
	
	virtual void Excute(IState* action) = 0;
};