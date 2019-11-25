//====================== 2019.11.24 ========================//
//================== MADE BY KIM WANKI =====================//
//======================== ACTOR ===========================//

#pragma once
#include "../GameObject.h"

class Actor : public GameObject
{
protected:
	enum ACTOR_STATE {
		DEFUALT,
		MOVE,
		ATTACK,
		DAMAGE,
		DIE
	};

protected:
	bool isAlive;

public:
	Actor();
	~Actor();

	// GameObject을(를) 통해 상속됨
	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	virtual Actor * Clone(void) = 0;
};

