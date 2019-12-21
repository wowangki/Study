#include "stdafx.h"
#include "RidgidBody.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Collider/RectCollider/RectCollider.h"
#include "../Collider/CircleCollider/CircleCollider.h"

DECLARE_COMPONENT(RidgidBody);

RidgidBody::RidgidBody(GameObject * object)
{
	this->object = object;
	useGravity = true;
	deltaTime = 0.0f;
	denyG = nullptr;

	if (!object->GetComponent<Collider>())
		object->AddComponent(new RectCollider(object))->Init();
}


RidgidBody::~RidgidBody()
{
}

HRESULT RidgidBody::Init(float mass, COLL_TYPE type)
{
	this->mass = mass;

	return S_OK;
}

void RidgidBody::Release(void)
{
	if (lOther.empty()) return;

	for (UINT i = 0; i < lOther.size(); i++)
	{
		(lOther.front())->Release();
	}
}

void RidgidBody::Update(void)
{
	Revision();
	GravityUpdate();
}

void RidgidBody::Render(void)
{
}

void RidgidBody::Revision(void)
{
	Collider* ownColl = object->GetComponent<Collider>();
	if (!ownColl) return;

	if (denyG) denyG = nullptr;
	if (lOther.empty()) return;

	Transform* transform = object->GetComponent<Transform>();
	for (UINT i = 0; i < lOther.size(); i++) {
		Collider* other = lOther.front() + i;
		D2D_POINT_2F reviScalar = { 0,0 };

		if (D2D_RECT_F* myColl = ownColl->GetCollBox().rc) {
			if (D2D_RECT_F* otherColl = other->GetCollBox().rc) {
				reviScalar = GetRevisionSize(myColl, otherColl);
			}
			else if (D2D1_ELLIPSE* otherColl = (lOther.front() + i)->GetCollBox().cir) {
				reviScalar = GetRevisionSize(myColl, otherColl);
			}
		}
		else if (D2D1_ELLIPSE* myColl = ownColl->GetCollBox().cir) {
			if (D2D_RECT_F* otherColl = (lOther.front() + i)->GetCollBox().rc) {
				reviScalar = GetRevisionSize(otherColl, myColl);
			}
			else if (D2D1_ELLIPSE* otherColl = (lOther.front() + i)->GetCollBox().cir) {
				reviScalar = GetRevisionSize(myColl, otherColl);
			}
		}

		if (!denyG) {
			if (abs(reviScalar.x) < abs(reviScalar.y) &&
				transform->GetWorldPos().y < other->GetTransform()->GetWorldPos().y) {
				denyG = other;
			}
			else denyG = nullptr;
		}

		transform->Translate({ reviScalar.x, reviScalar.y });
	}
}

void RidgidBody::GravityUpdate(void)
{
	if (!useGravity) return;

	Transform* transform = object->GetComponent<Transform>();
	if (transform->GetWorldPos().y + transform->GetSize().height * 0.5f >= WINSIZEY * 0.5f + 100 || denyG) {
		deltaTime = 0.0f;
		return;
	}
	
	deltaTime += _TIMER->GetElapsedTime();
	transform->Translate({ 0, GRAVITY * deltaTime });
}

D2D_POINT_2F RidgidBody::t_GetRevisionSize(Collider * other)
{
	Collider* ownColl = object->GetComponent<Collider>();

	if (D2D_RECT_F* ownRc = ownColl->GetCollBox().rc) {
		if (D2D_RECT_F* otherRc = other->GetCollBox().rc) {
			return GetRevisionSize(ownRc, otherRc);
		}
		else if (D2D1_ELLIPSE* otherCir = other->GetCollBox().cir) {
			return GetRevisionSize(ownRc, otherCir);
		}
	}
	else if (D2D1_ELLIPSE* ownCir = ownColl->GetCollBox().cir) {
		if (D2D_RECT_F* otherRc = other->GetCollBox().rc) {
			return GetRevisionSize(otherRc, ownCir);
		}
		else if (D2D1_ELLIPSE* otherCir = other->GetCollBox().cir) {
			return GetRevisionSize(ownCir, otherCir);
		}
	}
}
