#include "stdafx.h"
#include "RidgidBody.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Collider/RectCollider/RectCollider.h"
#include "../Collider/CircleCollider/CircleCollider.h"

RidgidBody::RidgidBody()
{
}

RidgidBody::RidgidBody(GameObject * object)
{
	this->object = object;

	transform = object->GetComponent<Transform>();

	if (object->GetComponent<RectCollider>()) {
		collider = object->GetComponent<RectCollider>();
	}
	else if (object->GetComponent<CircleCollider>()) {
		collider = object->GetComponent<CircleCollider>();
	}
	else {
		collider = object->AddComponent<RectCollider>();
		collider->Init();
	}
	useGravity = true;
	deltaTime = 0.0f;
}


RidgidBody::~RidgidBody()
{
}

HRESULT RidgidBody::Init(float mass)
{
	this->mass = mass;

	return S_OK;
}

void RidgidBody::Release(void)
{
	
}

void RidgidBody::Update(void)
{
	Revision();
	GravityUpdate();
}

void RidgidBody::Render(void)
{
}

void RidgidBody::IsCollision(Collider * other)
{
	if (collider->GetIsTrigger()) {
		collider->IsCollision(other);
	}
	else {
		bool isColl = collider->GetIsCollision();
		bool prevColl = isColl;

		if (dynamic_cast<RectCollider*>(collider)) {
			if (dynamic_cast<RectCollider*>(other)) {
				isColl = IsInRect(((RectCollider*)collider)->GetCollBox(),
								  ((RectCollider*)other)->GetCollBox());
			}
			else if (dynamic_cast<CircleCollider*>(other)) {
				isColl = IsRectInCircle(((RectCollider*)collider)->GetCollBox(),
										((CircleCollider*)other)->GetCollBox());
			}
		}
		else if (dynamic_cast<CircleCollider*>(collider)){
			if (dynamic_cast<RectCollider*>(other)) {
				isColl = IsRectInCircle(((RectCollider*)other)->GetCollBox(),
										((CircleCollider*)collider)->GetCollBox());
			}
			else if (dynamic_cast<CircleCollider*>(other)) {
				isColl = IsInCircle(((CircleCollider*)collider)->GetCollBox(),
									((CircleCollider*)other)->GetCollBox());
			}
		}

		collider->SetIsCollision(isColl);

		if (isColl) {
			if (!prevColl) {
				lOther.emplace_back(other);
				object->OnCollisionEnter(other);
			}
			else {
				object->OnCollisionStay(other);
			}
		}
		else {
			if (!prevColl) return;
			else {
				object->OnCollisionEnd(other);
				lOther.remove(other);
			}
		}
	}
	
}

void RidgidBody::Revision(void)
{
	if (lOther.empty()) return;

	for (UINT i = 0; i < lOther.size(); i++) {
		D2D_POINT_2F translate = { 0,0 };
		if (dynamic_cast<RectCollider*>(collider)) {
			if (dynamic_cast<RectCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((RectCollider*)collider)->GetCollBox(),
					((RectCollider*)(lOther.front() + i))->GetCollBox());
			}
			else if (dynamic_cast<CircleCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((RectCollider*)collider)->GetCollBox(),
					((CircleCollider*)(lOther.front() + i))->GetCollBox());
			}
		}
		else if (dynamic_cast<CircleCollider*>(collider)) {
			if (dynamic_cast<RectCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((RectCollider*)(lOther.front() + i))->GetCollBox(),
					((CircleCollider*)collider)->GetCollBox());
			}
			else if (dynamic_cast<CircleCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((CircleCollider*)collider)->GetCollBox(),
					((CircleCollider*)(lOther.front() + i))->GetCollBox());
			}
		}

		if (transform->GetWorldPos().y < (lOther.front() + i)->GetTransform()->GetWorldPos().y) {
			translate.y *= -1;
		}
		if (transform->GetWorldPos().x < (lOther.front() + i)->GetTransform()->GetWorldPos().x) {
			translate.x *= -1;
		}

		if (abs(translate.x) > abs(translate.y)) {
			transform->Translate({ 0, translate.y });
		}
		else if (abs(translate.x) < abs(translate.y)) {

			transform->Translate({ translate.x, 0 });
		}
		else {
			transform->Translate({ translate.x, translate.y });
		}
	}
}

void RidgidBody::GravityUpdate(void)
{
	if (!useGravity) return;
	Collider* temp = nullptr;
	deltaTime += _TIMER->GetElapsedTime();

	for (UINT i = 0; i < lOther.size(); i++)
	{
		D2D_POINT_2F translate = { 0,0 };
		if (dynamic_cast<RectCollider*>(collider)) {
			if (dynamic_cast<RectCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((RectCollider*)collider)->GetCollBox(),
					((RectCollider*)(lOther.front() + i))->GetCollBox());
			}
			else if (dynamic_cast<CircleCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((RectCollider*)collider)->GetCollBox(),
					((CircleCollider*)(lOther.front() + i))->GetCollBox());
			}
		}
		else if (dynamic_cast<CircleCollider*>(collider)) {
			if (dynamic_cast<RectCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((RectCollider*)(lOther.front() + i))->GetCollBox(),
					((CircleCollider*)collider)->GetCollBox());
			}
			else if (dynamic_cast<CircleCollider*>((lOther.front() + i))) {
				translate = GetOverlapSize(
					((CircleCollider*)collider)->GetCollBox(),
					((CircleCollider*)(lOther.front() + i))->GetCollBox());
			}
		}

		if (abs(translate.x) > abs(translate.y)) {
			temp = (lOther.front() + i);
			break;
		}
	}

	if (!temp) {
		if (transform->GetWorldPos().y + transform->GetSize().height * 0.5f >= WINSIZEY) {
			deltaTime = 0.0f;
			return;
		}
		transform->Translate({ 0, GRAVITY * deltaTime });
	}
	else {
		deltaTime = 0.0f;
	}
}
