#include "stdafx.h"
#include "TestObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Physics/Collider/CircleCollider/CircleCollider.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"
#include "../Component/Graphic/Animator/Animator.h"

TestObject::TestObject()
{
	_OBJMGR->RegistObjList(this);
	isActive = true;
	mode = OBJECT_MODE::DEFAULT;
	layer = LAYER::DEFAULT;
	AddComponent(new Transform(this))->Init({ 0,0 }, { 0,0 });
}

TestObject::TestObject(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, float angle)
{
	_OBJMGR->RegistObjList(this);
	isActive = true;
	mode = OBJECT_MODE::DEFAULT;
	layer = LAYER::DEFAULT;
	isControll = false;
	speed = 5.0f;
	AddComponent(new Transform(this))->Init(pos, size, pivot, angle);
	state = 0;
}

TestObject::~TestObject()
{
}

HRESULT TestObject::Init(void)
{
	//AddComponent(new RidgidBody(this))->Init(30.0f, RidgidBody::COLL_TYPE::RECTANGLE);
	AddComponent(new CircleCollider(this))->Init();
	AddComponent(new Animator(this))->AddSprite(state, "Test");

	return S_OK;
}

void TestObject::Release(void)
{
	mIter iter = mComponent.begin();
	for (iter; iter != mComponent.end(); ++iter) {
		SafeRelease(iter->second);
	}
	mComponent.clear();

	_OBJMGR->UnRegistObjList(this);
}

void TestObject::Update(void)
{
	mIter iter = mComponent.begin();
	for (iter; iter != mComponent.end(); ++iter) {
		iter->second->Update();
	}

	if (!isControll) return;

	D2D_POINT_2F translate = { 0,0 };
	if (_KEYCODE->StayKeyDown(VK_LEFT)) {
		translate.x -= 1.0f;
	}
	else if (_KEYCODE->StayKeyDown(VK_RIGHT)) {
		translate.x += 1.0f;
	}

	if (_KEYCODE->StayKeyDown(VK_UP)) {
		translate.y -= 1.0f;
	}
	else if(_KEYCODE->StayKeyDown(VK_DOWN)){
		translate.y += 1.0f;
	}

	translate = VectorNormalized(translate);

	GetComponent<Transform>()->Translate({ translate.x * speed, translate.y * speed });
}

void TestObject::Render(void)
{
	mIter iter = mComponent.begin();
	for (iter; iter != mComponent.end(); ++iter) {
		iter->second->Render();
	}
}

void TestObject::OnCollisionEnter(Collider * coll)
{
}

void TestObject::OnCollisionStay(Collider * coll)
{
}

void TestObject::OnCollisionEnd(Collider * coll)
{
}

void TestObject::OnTriggerEnter(Collider * coll)
{
}

void TestObject::OnTriggerStay(Collider * coll)
{
}

void TestObject::OnTriggerEnd(Collider * coll)
{
}
