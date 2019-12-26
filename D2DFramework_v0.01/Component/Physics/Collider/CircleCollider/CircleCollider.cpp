#include "stdafx.h"
#include "CircleCollider.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../RectCollider/RectCollider.h"
#include "../Interface/Collision/ICollision.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"


DECLARE_COMPONENT(CircleCollider);

CircleCollider::CircleCollider(GameObject * object)
{
	this->object = object;
	if (Collider* temp = object->GetComponent<Collider>()) {
		object->GetComponent<Transform>()->RemoveChild(temp->GetTransform());
	}

	transform = new Transform(this->object);
	this->isTrigger = false;
	this->isColl = false;

	_COLLMGR->RegistCollider(this);
}

CircleCollider::~CircleCollider()
{
}

HRESULT CircleCollider::Init(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, float angle)
{
	if (pos.x == 0.0f && pos.y == 0.0f) {
		transform->Init(object->GetComponent<Transform>());
	}
	else {
		transform->Init(pos, size, pivot, angle, object->GetComponent<Transform>());
	}

	collBox.cir = new D2D1_ELLIPSE;
	*collBox.cir = MakeCircle(transform->GetWorldPos(), transform->GetSize());
	collBox.rc = nullptr;

	return S_OK;
}


void CircleCollider::Release(void)
{
	SafeRelease(transform);
	
	_COLLMGR->UnRegistCollider(this);
}

void CircleCollider::Update(void)
{
	*collBox.cir = MakeCircle(transform->GetWorldPos(), transform->GetSize());
}

void CircleCollider::Render(void)
{
	_RenderTarget->DrawEllipse(collBox.cir, _Device->pDefaultBrush);
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

