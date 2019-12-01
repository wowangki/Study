//====================== 2019.11.24 ========================//
//================== MADE BY KIM WANKI =====================//
//================== MOVE STATE ============================//

#pragma once
#include "../IState.h"

class MoveState : public IState
{
private:
	float speed;

public:
	MoveState();
	explicit MoveState(float speed);
	~MoveState();

	virtual void Update(GameObject * object) override;
	
};
