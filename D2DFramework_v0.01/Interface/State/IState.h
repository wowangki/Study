//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== STATE INTERFACE =======================//

#pragma once

class GameObject;
class IState {
public:
	virtual void Update(GameObject* object) = 0;
};