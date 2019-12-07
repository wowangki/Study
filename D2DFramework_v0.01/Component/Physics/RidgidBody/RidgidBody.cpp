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
	denyG = nullptr;
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

		if (RectCollider* myCollider = dynamic_cast<RectCollider*>(collider)) {
			if (RectCollider* cachingOther = dynamic_cast<RectCollider*>(other)) {
				isColl = IsInRect(myCollider->GetCollBox(), cachingOther->GetCollBox());
			}
			else if (CircleCollider* cachingOther = dynamic_cast<CircleCollider*>(other)) {
				isColl = IsRectInCircle(myCollider->GetCollBox(), cachingOther->GetCollBox());
			}
		}
		else if (CircleCollider* myCollider = dynamic_cast<CircleCollider*>(collider)){
			if (RectCollider* cachingOther = dynamic_cast<RectCollider*>(other)) {
				isColl = IsRectInCircle(cachingOther->GetCollBox(), myCollider->GetCollBox());
			}
			else if (CircleCollider* cachingOther = dynamic_cast<CircleCollider*>(other)) {
				isColl = IsInCircle(myCollider->GetCollBox(), cachingOther->GetCollBox());
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
	if (denyG) denyG = nullptr;
	if (lOther.empty()) return;

	for (UINT i = 0; i < lOther.size(); i++) {
		D2D_POINT_2F translate = { 0,0 };
		if (RectCollider* myCollider = dynamic_cast<RectCollider*>(collider)) {
			if (RectCollider* cachingOther = dynamic_cast<RectCollider*>((lOther.front() + i))) {
				translate = GetRevisionSize(myCollider->GetCollBox(), cachingOther->GetCollBox());

				if (!denyG) {
					if (abs(translate.x) > abs(translate.y)) {
						denyG = cachingOther;
					}
					else denyG = nullptr;
				}

				if (transform->GetWorldPos().y < cachingOther->GetTransform()->GetWorldPos().y) {
					translate.y *= -1;
				}
				if (transform->GetWorldPos().x < cachingOther->GetTransform()->GetWorldPos().x) {
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
			else if (CircleCollider* cachingOther = dynamic_cast<CircleCollider*>((lOther.front() + i))) {
				translate = GetRevisionSize(myCollider->GetCollBox(), cachingOther->GetCollBox());
			}
		}
		else if (CircleCollider* myCollider = dynamic_cast<CircleCollider*>(collider)) {
			if (RectCollider* cachingOther = dynamic_cast<RectCollider*>((lOther.front() + i))) {
				translate = GetRevisionSize(cachingOther->GetCollBox(), myCollider->GetCollBox());
			}
			else if (CircleCollider* cachingOther = dynamic_cast<CircleCollider*>((lOther.front() + i))) {
				translate = GetRevisionSize(myCollider->GetCollBox(), cachingOther->GetCollBox());

				if (!denyG) {
					if (transform->GetWorldPos().x ==	cachingOther->GetTransform()->GetWorldPos().x &&
						transform->GetWorldPos().y < cachingOther->GetTransform()->GetWorldPos().y) {
						denyG = cachingOther;
					}
					else denyG = nullptr;
				}

				transform->Translate({ translate.x, translate.y });
			}
		}
	}
}

void RidgidBody::GravityUpdate(void)
{
	if (!useGravity) return;
	if (transform->GetWorldPos().y + transform->GetSize().height * 0.5f >= WINSIZEY * 0.5f || denyG) {
		deltaTime = 0.0f;
		return;
	}
	
	deltaTime += _TIMER->GetElapsedTime();
	transform->Translate({ 0, GRAVITY * deltaTime });
}
