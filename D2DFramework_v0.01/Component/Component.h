//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Component Base ========================//

#pragma once

// Abstract Class
class GameObject;
class Component {
protected:
	GameObject* object;

public:
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;

};