#include "stdafx.h"
#include "RectCollider.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../CircleCollider/CircleCollider.h"
#include "../Interface/Collision/ICollision.h"
#include "../Manager/Collision/CollisionManager.h"

RectCollider::RectCollider()
{
}

RectCollider::RectCollider(GameObject * object)
{
	this->object = object;
	//this->object->GetCollMgr()->AddCollider(this);
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

	collBox = transform->GetRect();

	return S_OK;
}

void RectCollider::Release(void)
{
	SafeRelease(transform);
}

void RectCollider::Update(void)
{
	collBox = transform->GetRect();
}

void RectCollider::Render(void)
{
	_RenderTarget->DrawRectangle(collBox, _Device->pDefaultBrush);
}

void RectCollider::IsCollision(Collider * col)
{
	if (!isTrigger) return;

	bool prevColl = isColl;

	if (RectCollider* other = dynamic_cast<RectCollider*>(col)) {
		isColl = IsInRect(collBox, other->GetCollBox());
	}
	else if (CircleCollider* other = dynamic_cast<CircleCollider*>(col)) {
		isColl = IsRectInCircle(collBox, other->GetCollBox());
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