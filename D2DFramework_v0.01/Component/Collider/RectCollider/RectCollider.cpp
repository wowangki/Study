#include "stdafx.h"
#include "RectCollider.h"
#include "../Component/Transform/Transform.h"
#include "../CircleCollider/CircleCollider.h"
#include "../Interface/Collision/ICollision.h"

RectCollider::RectCollider()
{
}

RectCollider::RectCollider(ICollision * myObject)
{
	this->myObject = myObject;
	this->isColl = false;
}

RectCollider::~RectCollider()
{
}

HRESULT RectCollider::Init(void)
{
	if (FAILED(PopErrorBox(transform))) {
		Release();
		return E_FAIL;
	}

	figure = MakeRect(transform->GetPos(), transform->GetSize(), transform->GetPivot());

	return S_OK;
}

void RectCollider::Release(void)
{
	SafeRelease(transform);
}

void RectCollider::Update(void)
{
	figure = MakeRect(transform->GetPos(), transform->GetSize(), transform->GetPivot());
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
