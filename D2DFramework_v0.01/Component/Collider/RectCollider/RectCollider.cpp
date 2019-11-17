#include "stdafx.h"
#include "RectCollider.h"
#include "../Component/Transform/Transform.h"
#include "../CircleCollider/CircleCollider.h"
#include "../GameObject/GameObject.h"

RectCollider::RectCollider()
{
}

RectCollider::RectCollider(Transform * transform, PIVOT pivot, bool isColl)
{
	this->transform = transform;
	this->pivot = pivot;
	this->isColl = isColl;

	figure = MakeRect(transform->GetPos(), transform->GetSize(), this->pivot);
}

RectCollider::RectCollider(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, bool isColl)
{
	transform = new Transform(pos, size);
	this->pivot = pivot;
	this->isColl = isColl;

	figure = MakeRect(transform->GetPos(), transform->GetSize(), this->pivot);
}


RectCollider::~RectCollider()
{
}

void RectCollider::Init(void)
{
}

void RectCollider::Release(void)
{
	SafeRelease(transform);
}

void RectCollider::Update(void)
{
	figure = MakeRect(transform->GetPos(), transform->GetSize(), this->pivot);
}

void RectCollider::Render(void)
{
	_RenderTarget->DrawRectangle(figure, _Device->pDefaultBrush);
}

void RectCollider::IsCollision(Collider * col)
{
	if (!col) return;
	bool hasColl;

	if (typeid(*col) == typeid(RectCollider)) {
		hasColl = IsInRect(figure, ((RectCollider*)col)->GetFigure());
	}
	else if (typeid(*col) == typeid(CircleCollider)) {
		hasColl = IsRectInCircle(figure, ((CircleCollider*)col)->GetFigure());
	}
	
	if (hasColl) {
		if (!isColl) {
			isColl = true;
			//myObject->IsOnCollisionEnter(col);
		}
		else {
			//myObject->IsCollisionStay(col);
		}
	}
	else {
		if (!isColl) return;
		else {
			//myObject->IsOnCollisionEnd(col);
		}
	}
}
