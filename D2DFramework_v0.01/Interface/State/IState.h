//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== STATE INTERFACE =======================//

#pragma once

class ICommand;
class IState {
public:
	virtual void Update(ICommand* com) = 0;
};