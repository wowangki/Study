//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== GAME OBJECT ===========================//

#pragma once
#include <unordered_map>
#include "../Component/Component.h"
#include "../Interface/Collision/ICollision.h"

enum class OBJECT_MODE { DEFAULT, INGAME, TOOLSET };
enum class LAYER { DEFAULT, PLAYER, ENEMY, MAP, UI, MAPOBJECT };

class Component;
class CollisionManager;
class GameObject : public ICollision, ITrigger
{
protected:
	class GameObjectManager* mgr;

protected:
	unordered_map<size_t, Component*> mComponent;
	typedef unordered_map<size_t, Component*>::iterator mIter;

protected:
	int id;
	string name;
	string tag;

	int state;
	bool isActive;
	OBJECT_MODE mode;
	LAYER layer;

protected:
	CollisionManager* collMgr;

public:
	virtual HRESULT Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	
	template<class Component_t>
	inline Component_t* AddComponent(Component_t* component)
	{
		size_t componentId = get_component<Component_t>::type::getComponentId();

		this->mComponent[componentId] = component;
		
		return reinterpret_cast<Component_t*>(mComponent[componentId]);
	}

	template<class Component_t>
	inline Component_t * GetComponent(void)
	{
		if (mComponent.empty()) return nullptr;
		
		size_t componentId = get_component<Component_t>::type::getComponentId();
		
		if (mComponent.find(componentId) == mComponent.end()) return nullptr;
		
		return reinterpret_cast<Component_t*>(mComponent[componentId]);
	}

	template<class Component_t>
	inline void RemoveComponent(void) {
		if (mComponent.empty()) return;

		size_t componentId = get_component<Component_t>::type::getComponentId();

		if (mComponent.find(componentId) != mComponent.end()) 
			mComponent.erase(componentId);
	}

	inline int GetID(void) { return id; }
	inline string GetName(void) { return name; }
	inline string GetTag(void) { return tag; }
	inline int GetState(void) { return state; }
	inline bool GetActive(void) { return isActive; }
	inline OBJECT_MODE GetMode(void) { return mode; }
	inline LAYER GetLayer(void) { return layer; }
	inline CollisionManager* GetCollMgr(void) { return collMgr; }

	void SetName(string name) { this->name = name; }
	void SetTag(string tag) { this->tag = tag; }
	void SetState(int state) { this->state = state; }
	void SetActive(bool isActive) { this->isActive = isActive; }
	void SetMode(OBJECT_MODE mode) { this->mode = mode; }
	void SetLayer(LAYER layer) { this->layer = layer; }

	//Interface Pure Abstract Fuction

	// ICollision을(를) 통해 상속됨
	virtual void OnCollisionEnter(Collider * coll) = 0;
	virtual void OnCollisionStay(Collider * coll) = 0;
	virtual void OnCollisionEnd(Collider * coll) = 0;

	// ITrigger을(를) 통해 상속됨
	virtual void OnTriggerEnter(Collider * coll) = 0;
	virtual void OnTriggerStay(Collider * coll) = 0;
	virtual void OnTriggerEnd(Collider * coll) = 0;
};