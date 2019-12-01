#include "stdafx.h"
#include "UICollider.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Interface/UI/IUI.h"
#include "../GameObject/UI/UI.h"

UICollider::UICollider()
{
}

UICollider::UICollider(UI* ui, UICOL_TYPE type)
{
	this->object = ui;
	SetHandler(ui);
	this->type = type;

	transform = this->object->GetComponent<Transform>();
	isTrigger = true;
	isColl = false;
	
}

UICollider::~UICollider()
{
}

void UICollider::Release(void)
{
	SafeDelete(upHandler);
	SafeDelete(downHandler);
	SafeDelete(dragHandler);
}

void UICollider::Update(void)
{
	switch (type) {
	case UI_RECT:
		rc = MakeRect(transform->GetWorldPos(), transform->GetSize(), transform->GetPivot());
		break;
	case UI_CIR:
		cir = MakeCircle(transform->GetWorldPos(), transform->GetSize());
		break;
	}
}

void UICollider::Render(void)
{
	switch (type) {
	case UI_RECT:
		_RenderTarget->DrawRectangle(rc, _Device->pDefaultBrush);
		break;
	case UI_CIR:
		_RenderTarget->DrawEllipse(cir, _Device->pDefaultBrush);
		break;
	}
}

void UICollider::IsCollision(void)
{
	D2D_POINT_2F mousePointer = { (float)GET_X_LPARAM(AppMouse.x), (float)GET_Y_LPARAM(AppMouse.y) };

	bool prevColl = isColl;

	switch (type) {
	case UI_RECT:
		isColl = IsInRectPoint(rc, mousePointer);
		break;
	case UI_CIR:
		isColl = IsInCirPoint(cir, mousePointer);
		break;
	}

	if (isColl) {
		if (_KEYCODE->IsKeyDown(VK_LBUTTON) && downHandler) {
			downHandler->OnPointDown();
		}
		else if (_KEYCODE->StayKeyDown(VK_LBUTTON) && dragHandler) {
			dragHandler->OnDragPointer();
		}
	}
	else {
		if (!prevColl) return;
		else {
			if (_KEYCODE->IsKeyUp(VK_LBUTTON) && upHandler) {
				upHandler->OnPointUp();
			}
		}
	}
	
}

void UICollider::SetHandler(UI * ui)
{
	upHandler = nullptr;
	downHandler = nullptr;
	dragHandler = nullptr;
	
	if (dynamic_cast<IPointerUpHandler*>(ui)) {
		upHandler = (IPointerUpHandler*)ui;
	}

	if (dynamic_cast<IPointerDownHandler*>(ui)) {
		downHandler = (IPointerDownHandler*)ui;
	}

	if (dynamic_cast<IDragHandler*>(ui)) {
		dragHandler = (IDragHandler*)ui;
	}
}
