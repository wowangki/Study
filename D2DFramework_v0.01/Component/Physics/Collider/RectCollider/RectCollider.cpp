#include "stdafx.h"
#include "RectCollider.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../CircleCollider/CircleCollider.h"
#include "../Interface/Collision/ICollision.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"

DECLARE_COMPONENT(RectCollider);

RectCollider::RectCollider(GameObject * object)
{
	_COLLMGR->RegistCollider(this);
	this->object = object;
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

HRESULT RectCollider::Init(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, float angle)
{
	if (pos.x == 0.0f && pos.y == 0.0f) {
		transform->Init(object->GetComponent<Transform>());
	}
	else {
		transform->Init(pos, size, pivot, angle, object->GetComponent<Transform>());
	}

	
	collBox.rc = new D2D_RECT_F;
	*collBox.rc = MakeRect(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());

	collBox.cir = nullptr;

	return S_OK;
}

void RectCollider::Release(void)
{
	SafeRelease(transform);
	_COLLMGR->UnRegistCollider(this);
}

void RectCollider::Update(void)
{
	*collBox.rc = MakeRect(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());
}

void RectCollider::Render(void)
{
	_RenderTarget->DrawRectangle(collBox.rc, _Device->pDefaultBrush);
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