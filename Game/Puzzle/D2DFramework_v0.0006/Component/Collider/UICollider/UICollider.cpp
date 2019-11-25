#include "stdafx.h"
#include "UICollider.h"
#include "../Component/Transform/Transform.h"
#include "../Interface/UI/IUI.h"
#include "../GameObject/UI/UI.h"

UICollider::UICollider()
{
}

UICollider::UICollider(UI* myUI, UICOL_TYPE type)
{
	SetHandler(myUI);
	this->type = type;
	this->isColl = false;
}

UICollider::~UICollider()
{
}

HRESULT UICollider::Init(void)
{
	if (FAILED(PopErrorBox(transform))) {
		Release();
		return E_FAIL;
	}

	switch (type) {
	case UI_RECT:
		rc = MakeRect(transform->GetPos(), transform->GetSize(), transform->GetPivot());
		break;
	case UI_CIR:
		cir = MakeCircle(transform->GetPos(), transform->GetSize());
		break;
	}

	return S_OK;
}

void UICollider::Release(void)
{
}

void UICollider::Update(void)
{
	switch (type) {
	case UI_RECT:
		rc = MakeRect(transform->GetPos(), transform->GetSize(), transform->GetPivot());
		break;
	case UI_CIR:
		cir = MakeCircle(transform->GetPos(), transform->GetSize());
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

	bool hasColl;

	switch (type) {
	case UI_RECT:
		hasColl = IsInRectPoint(rc, mousePointer);
		break;
	case UI_CIR:
		hasColl = IsInCirPoint(cir, mousePointer);
		break;
	}

	if (hasColl) {
		if (_KEYCODE->IsKeyDown(VK_LBUTTON)) {
			if (!downHandler) return;
			isColl = true;
			downHandler->OnPointDown(this);
		}
		else {
			if (!dragHandler) return;
			dragHandler->OnDragPointer(this);
		}
	}
	else {
		if (!isColl) return;
		else {
			if (_KEYCODE->IsKeyUp(VK_LBUTTON)) {
				if (!upHandler) return;
				upHandler->OnPointUp(this);
			}
		}
	}
	
}

void UICollider::SetHandler(UI * myUI)
{
	upHandler = nullptr;
	downHandler = nullptr;
	dragHandler = nullptr;

	if (typeid(*myUI) == typeid(IPointerUpHandler*)) {
		upHandler = (IPointerUpHandler*)myUI;
	}

	if (typeid(*myUI) == typeid(IPointerDownHandler*)) {
		downHandler = (IPointerDownHandler*)myUI;
	}

	if (typeid(*myUI) == typeid(IDragHandler*)) {
		dragHandler = (IDragHandler*)myUI;
	}
}
