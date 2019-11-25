#include "stdafx.h"
#include "CircleCollider.h"
#include "../Component/Transform/Transform.h"
#include "../RectCollider/RectCollider.h"
#include "../Interface/Collision/ICollision.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(ICollision * myObject)
{
	this->myObject = myObject;
	this->isColl = false;
}

CircleCollider::~CircleCollider()
{
}

HRESULT CircleCollider::Init(void)
{
	if (FAILED(PopErrorBox(transform))) {
		Release();
		return E_FAIL;
	}

	figure = MakeCircle(transform->GetPos(), transform->GetSize());
	return S_OK;
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
		col->GetTransform()->Translate(GetGapDistance(transform->GetPos(), transform->GetSize(),
										col->GetTransform()->GetPos(), col->GetTransform()->GetSize()));

		if (!isColl) {
			isColl = true;
			myObject->OnCollisionEnter(col);
		}
		else {
			myObject->OnCollisionStay(col);
		}
	}
	else {
		if (!isColl) return;
		else {
			myObject->OnCollisionEnd(col);
		}
	}
}