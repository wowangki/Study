#include "stdafx.h"
#include "UICollider.h"
#include "../Manager/World/WorldMgr.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Interface/UI/IUI.h"
#include "../GameObject/UI/UI.h"

DECLARE_COMPONENT(UICollider);

UICollider::UICollider(UI* ui, UICOL_TYPE type)
{
	this->object = ui;
	this->object->GetWorld()->RegistPhysics(this);
	SetHandler(ui);
	this->type = type;

	if (Collider* temp = object->GetComponent<Collider>()) {
		object->GetComponent<Transform>()->RemoveChild(temp->GetTransform());
	}

	transform = this->object->GetComponent<Transform>();
	isTrigger = true;
	isColl = false;

	switch (type)
	{
	case UI_RECT:default:
		collBox.rc = new D2D_RECT_F(transform->GetRect());
		collBox.cir = nullptr;
		break;
	case UI_CIR:
		collBox.cir = new D2D1_ELLIPSE(MakeCircle(transform->GetWorldPos(), transform->GetSize()));
		collBox.rc = nullptr;
		
		break;
	}
	
}

UICollider::~UICollider()
{
}

void UICollider::Release(void)
{
	SafeDelete(upHandler);
	SafeDelete(downHandler);
	SafeDelete(dragHandler);
	SafeDelete(collBox.rc);
	SafeDelete(collBox.cir);
	this->object->GetWorld()->UnRegistPhysics(this);
}

void UICollider::Update(void)
{
	switch (type) {
	case UI_RECT:default:
		*collBox.rc = MakeRect(transform->GetWorldPos(), transform->GetSize());
		break;
	case UI_CIR:
		*collBox.cir = MakeCircle(transform->GetWorldPos(), transform->GetSize());
		break;
	}
}

void UICollider::IsCollision(void)
{
	D2D_POINT_2F mousePointer = { (float)GET_X_LPARAM(AppMouse.x), (float)GET_Y_LPARAM(AppMouse.y) };

	bool prevColl = isColl;

	switch (type) {
	case UI_RECT:
		isColl = IsInRectPoint(collBox.rc, mousePointer);
		break;
	case UI_CIR:
		isColl = IsInCirPoint(collBox.cir, mousePointer);
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