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
	Transform* transform;
	Collider* collider;

	float mass;
	float deltaTime;
	bool useGravity;
private:
	list<Collider*> lOther;
	Collider* denyG;

public:
	RidgidBody();
	explicit RidgidBody(GameObject* object);
	~RidgidBody();

	// Component을(를) 통해 상속됨
	virtual HRESULT Init(float mass);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void IsCollision(Collider* other);
	void Revision(void);
	void GravityUpdate(void);
	
};

