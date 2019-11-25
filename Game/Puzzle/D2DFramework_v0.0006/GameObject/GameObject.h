//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== GAME OBJECT ===========================//

#pragma once
#include <vector>

enum class OBJECT_MODE { DEFAULT, INGAME, TOOLSET };
enum class LAYER { DEFAULT, PLAYER, ENEMY, MAP, UI, MAPOBJECT };

class Component;
class GameObject
{
protected:
	vector<Component*> vComponent;

protected:
	bool isActive;
	OBJECT_MODE mode;
	LAYER layer;

public:

	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	
	template<typename T>
	T* AddComponent(void) { 
		Component* temp = new T(this);
		if (dynamic_cast<Component*>(temp)) {
			vComponent.emplace_back(temp);
			return (T*)vComponent[vComponent.size() - 1];
		}
		else return nullptr;
	}

	template<typename T>
	T* GetComponent(void) {
		for (int i = 0; i < vComponent.size(); i++) {
			if (dynamic_cast<T*>(vComponent[i])) {
				return (T*)vComponent[i];
			}
		}

		return nullptr;
	}
};

