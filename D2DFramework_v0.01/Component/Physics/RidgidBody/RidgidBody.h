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

public:
	RidgidBody();
	explicit RidgidBody(GameObject* object);
	~RidgidBody();

	// Component��(��) ���� ��ӵ�
	virtual HRESULT Init(float mass);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void Revision(void);
	void IsCollision(Collider* other);
	void GravityUpdate(void);
	
};

