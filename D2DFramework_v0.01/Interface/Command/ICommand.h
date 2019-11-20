//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== COMMAND INTERFACE =====================//

#pragma once

class GameObject;
class ICommand {
public:
	virtual void Excute(GameObject* actor) = 0;
};