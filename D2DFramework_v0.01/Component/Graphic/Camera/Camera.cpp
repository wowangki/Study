#include "stdafx.h"
#include "Camera.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Manager/World/WorldMgr.h"

DECLARE_COMPONENT(Camera);

Camera::Camera(GameObject * object)
	:scale(1.0f)
{
	this->object = object;
	target = nullptr;
	transform = new Transform(this->object);
	this->object->GetWorld()->RegistCamera(this);
}

Camera::~Camera()
{
}


HRESULT Camera::Init(D2D_SIZE_F size, D2D_POINT_2F offset)
{
	transform->Init(offset, size, PIVOT_CC, 0.0f, this->object->GetComponent<Transform>());

	return S_OK;
}

void Camera::Release(void)
{
	this->object->GetWorld()->UnRegistCamera(this);
	transform = nullptr;
	this->object = nullptr;
	target = nullptr;
}

void Camera::Update(void)
{
	TestControll();
}

void Camera::ZoomIn(void)
{
	if (scale >= MAXZOOM) return;
	scale += 0.1f;
}

void Camera::ZoomOut(void)
{
	if (scale <= MINZOOM) return;
	scale -= 0.1f;
}

D2D_POINT_2F Camera::GetRevisionPos(void) const
{
	D2D_POINT_2F temp;

	if (!target) {
		temp.x = (WINSIZEX * 0.5f - transform->GetWorldPos().x);
		temp.y = (WINSIZEY * 0.5f - transform->GetWorldPos().y);
	}
	else {
		temp.x = (WINSIZEX * 0.5f - target->GetComponent<Transform>()->GetWorldPos().x);
		temp.y = (WINSIZEY * 0.5f - target->GetComponent<Transform>()->GetWorldPos().y);
	}
	
	return temp;
}

D2D_RECT_F Camera::GetCamRect(void) const
{
	D2D_RECT_F rc;
	
	if (!target) {
		rc = MakeRect(
			{ transform->GetWorldPos().x + GetRevisionPos().x,
			  transform->GetWorldPos().y + GetRevisionPos().y },
			transform->GetSize(), transform->GetPivot());
	}
	else {
		rc = MakeRect(
			{ target->GetComponent<Transform>()->GetWorldPos().x + GetRevisionPos().x,
			target->GetComponent<Transform>()->GetWorldPos().y + GetRevisionPos().y },
			transform->GetSize(), transform->GetPivot());
	}

	return rc;
}

void Camera::SetScale(float scale)
{
	if (scale <= MINZOOM) {
		this->scale = MINZOOM;
	}
	else if (scale >= MAXZOOM) {
		this->scale = MAXZOOM;
	}
	else {
		this->scale = scale;
	}
}

void Camera::TestControll(void)
{
	D2D_POINT_2F direction = { 0,0 };
	float camSpeed = 3.0f;
	
	if (_KEYCODE->StayKeyDown('W')) {
		direction.y -= 1.0f;
	}
	else if (_KEYCODE->StayKeyDown('S')) {
		direction.y += 1.0f;
	}
	
	if (_KEYCODE->StayKeyDown('A')) {
		direction.x -= 1.0f;
	}
	else if (_KEYCODE->StayKeyDown('D')) {
		direction.x += 1.0f;
	}
	
	direction = VectorNormalized(direction);

	transform->Translate({ direction.x * camSpeed, direction.y * camSpeed });
}