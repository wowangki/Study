//====================== 2019.11.29 ========================//
//================== MADE BY KIM WANKI =====================//
//================== RIDGIDBODY =========================//

#pragma once
#include "../Component/Component.h"
#include <list>
#define GRAVITY 9.80665f

class Transform;
class Collider;
class RidgidBody final : public Component
{
private:
	DEFINE_COMPONENT(RidgidBody, Component, false);

public:
	enum COLL_TYPE {
		RECTANGLE,
		CIRCLE
	};

private:
	float mass;
	float deltaTime;
	bool useGravity;
private:
	list<Collider*> lOther;
	Collider* denyG;

public:
	explicit RidgidBody(GameObject* object);
	~RidgidBody();

	// Component을(를) 통해 상속됨
	virtual HRESULT Init(float mass, COLL_TYPE type = RECTANGLE);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void Revision(void);
	void GravityUpdate(void);
	
	inline void AddCollider(Collider* other) { lOther.push_back(other); }
	inline void DeleteColl(Collider* other) { 
		if (lOther.empty()) return; 
		lOther.remove(other); 
	}

	// TEST 전용

	D2D_POINT_2F t_GetRevisionSize(Collider* other);
};