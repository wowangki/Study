#include "stdafx.h"
#include "CircleCollider.h"
#include "../Manager/World/WorldMgr.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../RectCollider/RectCollider.h"
#include "../Interface/Collision/ICollision.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"


DECLARE_COMPONENT(CircleCollider);

CircleCollider::CircleCollider(GameObject * object)
{
	this->object = object;
	//this->object->GetWorld()->RegistPhysics(this);
	if (Collider* temp = object->GetComponent<Collider>()) {
		object->GetComponent<Transform>()->RemoveChild(temp->GetTransform());
	}

	transform = new Transform(this->object);
	this->isTrigger = false;
	this->isColl = false;
}

CircleCollider::~CircleCollider()
{
}

HRESULT CircleCollider::Init(void)
{
	transform->Init(object->GetComponent<Transform>());
	collBox.cir = new D2D1_ELLIPSE;
	*collBox.cir = MakeCircle(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());
	collBox.rc = nullptr;
	return S_OK;
}


HRESULT CircleCollider::Init(D2D_POINT_2F pos, D2D_SIZE_F size, float angle)
{
	transform->Init(pos, size, object->GetComponent<Transform>()->GetPivot(), angle, object->GetComponent<Transform>());
	collBox.cir = new D2D1_ELLIPSE;
	*collBox.cir = MakeCircle(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());
	collBox.rc = nullptr;

	return S_OK;
}


void CircleCollider::Release(void)
{
	SafeRelease(transform);
	//this->object->GetWorld()->UnRegistPhysics(this);
}

void CircleCollider::Update(void)
{
	*collBox.cir = MakeCircle(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());
}

void CircleCollider::IsCollision(Collider * other)
{
	bool prevColl = isColl;

	if (other->GetCollBox().rc) {
		isColl = IsRectInCircle(other->GetCollBox().rc, collBox.cir);
	}
	else if (other->GetCollBox().cir) {
		isColl = IsInCircle(collBox.cir, other->GetCollBox().cir);
	}

	RidgidBody* ridgid = nullptr;
	if (isColl) {
		if (!prevColl) {
			if (!isTrigger) {
				object->OnCollisionEnter(other);

				if ((ridgid = object->GetComponent<RidgidBody>())) {
					ridgid->AddCollider(other);
				}
			}
			else object->OnTriggerEnter(other);
		}
		else {
			if (!isTrigger) {
				object->OnCollisionStay(other);
			}
			else object->OnTriggerStay(other);
		}
	}
	else {
		if (!prevColl) return;
		else {
			if (!isTrigger) {
				object->OnCollisionEnd(other);

				if ((ridgid = object->GetComponent<RidgidBody>())) {
					ridgid->DeleteColl(other);
				}
			}
			else object->OnTriggerEnd(other);
		}
	}
}

