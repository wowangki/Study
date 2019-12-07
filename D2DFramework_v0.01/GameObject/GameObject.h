//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== GAME OBJECT ===========================//

#pragma once
#include <map>
#include "../Interface/Collision/ICollision.h"

enum class OBJECT_MODE { DEFAULT, INGAME, TOOLSET };
enum class LAYER { DEFAULT, PLAYER, ENEMY, MAP, UI, MAPOBJECT };

class Component;
class CollisionManager;
class GameObject : public ICollision, ITrigger
{
protected:
	map<string, Component*> mComponent;
	typedef map<string, Component*>::iterator mIter;

protected:
	static int s_id;
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
	
	template<typename T>
	inline T* AddComponent(void)
	{
		Component* temp = GetComponent<T>();
		if (temp) return (T*) temp;
		
		temp = new T(this);
		mComponent.insert(make_pair(typeid(T).name(), temp));

		return (T*)temp;
	}

	template<typename T>
	inline T * GetComponent(void)
	{
		if (mComponent.empty()) return nullptr;

		mIter iter = mComponent.begin();

		for (iter; iter != mComponent.end(); ++iter) {
			if (iter->first == typeid(T).name()) {
				return (T*)iter->second;
			}
		}

		return nullptr;
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