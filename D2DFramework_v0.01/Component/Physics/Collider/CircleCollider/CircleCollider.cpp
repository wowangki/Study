#include "stdafx.h"
#include "CircleCollider.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../RectCollider/RectCollider.h"
#include "../Interface/Collision/ICollision.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(GameObject * object)
{
	this->object = object;
	transform = new Transform(this->object);
	this->isTrigger = false;
	this->isColl = false;
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

	collBox = MakeCircle(transform->GetWorldPos(), transform->GetSize());

	return S_OK;
}


void CircleCollider::Release(void)
{
	SafeRelease(transform);
}

void CircleCollider::Update(void)
{
	collBox = MakeCircle(transform->GetWorldPos(), transform->GetSize());
}

void CircleCollider::Render(void)
{
	_RenderTarget->DrawEllipse(collBox, _Device->pDefaultBrush);
}

void CircleCollider::IsCollision(Collider * col)
{
	if (!isTrigger) return;

	bool prevColl = isColl;

	if (typeid(*col) == typeid(RectCollider)) {
		isColl = IsRectInCircle(((RectCollider*)col)->GetCollBox(), collBox);
	}
	else if (typeid(*col) == typeid(CircleCollider)) {
		isColl = IsInCircle(collBox, ((CircleCollider*)col)->GetCollBox());
	}

	if (isColl) {
		if (!prevColl) {
			object->OnTriggerEnter(col);
		}
		else {
			object->OnTriggerStay(col);
		}
	}
	else {
		if (!prevColl) return;
		else {
			object->OnTriggerEnd(col);
		}
	}
}

