//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Component Base ========================//

#pragma once
#include "ComponentHelper.h"

// Abstract Class
class GameObject;
class Component {
protected:
	GameObject* object;

private:
	DEFINE_COMPONENT(Component, null_t, false);

public:
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;

	inline GameObject* GetMyObject(void) { return object; }
};