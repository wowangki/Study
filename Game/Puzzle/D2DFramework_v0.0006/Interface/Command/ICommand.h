//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== COMMAND INTERFACE =====================//

#pragma once

class IState;
class ICommand {
public:
	virtual void Excute(IState* state) = 0;
};