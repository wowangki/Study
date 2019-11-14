#include "stdafx.h"
#include "RectCollider.h"
#include "../Module/Transform/Transform.h"
#include "../CollMediator/CollisionMediator.h"
#include "../GameObject/GameObject.h"

RectCollider::RectCollider()
{
	transform = nullptr;
	pivot = PIVOT_LT;
	onTrigger = false;
	isCollision = false;
}

RectCollider::RectCollider(GameObject * object, Transform * transform, PIVOT pivot, bool onTrigger, CollisionMediator * mediator)
{
	this->object = object;
	this->transform = transform;
	this->pivot = pivot;
	this->isCollision = false;
	this->onTrigger = onTrigger;
	collider = MakeRect(transform->GetPos(), transform->GetSize(), this->pivot);

	if (mediator) mediator->AddCollider(this);
}


RectCollider::~RectCollider()
{
}

void RectCollider::Update(ColliderBase* coll)
{
	collider = MakeRect(transform->GetPos(), transform->GetSize(), this->pivot);

	if (!isCollision) {
		if (!coll) return;
		object->OnCollisionEnter(coll);
		isCollision = true;
	}
	else {
		if (!coll) {
			//object->OnCollisionExit(coll);
			isCollision = false;
		}
		object->OnCollisionStay(coll);
	}

}

void RectCollider::Render(void)
{
	_RenderTarget->DrawRectangle(collider, _COLOR->GetBrush(_COLOR->WHITE));
}
