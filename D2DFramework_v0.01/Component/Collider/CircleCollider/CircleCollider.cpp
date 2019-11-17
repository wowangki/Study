#include "stdafx.h"
#include "CircleCollider.h"
#include "../Component/Transform/Transform.h"
#include "../RectCollider/RectCollider.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(Transform * transform, PIVOT pivot, bool isColl)
{
	this->transform = transform;
	this->pivot = pivot;
	this->isColl = isColl;

	figure = MakeCircle(transform->GetPos(), transform->GetSize());
}

CircleCollider::CircleCollider(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, bool isColl)
{
	transform = new Transform(pos, size);
	this->pivot = pivot;
	this->isColl = isColl;
	figure = MakeCircle(transform->GetPos(), transform->GetSize());
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Init(void)
{
}

void CircleCollider::Release(void)
{
	SafeRelease(transform);
}

void CircleCollider::Update(void)
{
	figure = MakeCircle(transform->GetPos(), transform->GetSize());
}

void CircleCollider::Render(void)
{
	_RenderTarget->DrawEllipse(figure, _Device->pDefaultBrush);
}

void CircleCollider::IsCollision(Collider * col)
{
	if (!col) return;
	bool hasColl;

	if (typeid(*col) == typeid(RectCollider)) {
		hasColl = IsRectInCircle(((RectCollider*)col)->GetFigure(), figure);
	}
	else if (typeid(*col) == typeid(CircleCollider)) {
		hasColl = IsInCircle(figure, ((CircleCollider*)col)->GetFigure());
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
