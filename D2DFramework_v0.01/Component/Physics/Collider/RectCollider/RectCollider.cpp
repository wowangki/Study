#include "stdafx.h"
#include "RectCollider.h"
#include "../Manager/World/WorldMgr.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../CircleCollider/CircleCollider.h"
#include "../Interface/Collision/ICollision.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"

DECLARE_COMPONENT(RectCollider);

RectCollider::RectCollider(GameObject * object)
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

RectCollider::~RectCollider()
{
}

HRESULT RectCollider::Init(void)
{
	transform->Init(object->GetComponent<Transform>());

	collBox.rc = new D2D_RECT_F;
	*collBox.rc = MakeRect(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());

	collBox.cir = nullptr;

	return S_OK;
}


HRESULT RectCollider::Init(D2D_POINT_2F pos, D2D_SIZE_F size, float angle)
{
	transform->Init(pos, size, object->GetComponent<Transform>()->GetPivot(), angle, object->GetComponent<Transform>());

	collBox.rc = new D2D_RECT_F;
	*collBox.rc = MakeRect(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());

	collBox.cir = nullptr;

	return S_OK;
}

void RectCollider::Release(void)
{
	SafeRelease(transform);
	//this->object->GetWorld()->UnRegistPhysics(this);
}

void RectCollider::Update(void)
{
	*collBox.rc = MakeRect(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());
}

void RectCollider::IsCollision(Collider * other)
{
	bool prevColl = isColl;

	if (other->GetCollBox().rc) {
		isColl = IsInRect(collBox.rc, other->GetCollBox().rc);
	}
	else if (other->GetCollBox().cir) {
		isColl = IsRectInCircle(collBox.rc, other->GetCollBox().cir);
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
