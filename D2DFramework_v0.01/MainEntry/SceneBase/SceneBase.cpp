#include "stdafx.h"
#include "SceneBase.h"
#include "../Manager/World/WorldMgr.h"
#include "../GameObject/TestObject/TestObject.h"
#include "../GameObject/TestObject/MainCamera.h"
#include "../Component/Physics/Collider/RectCollider/RectCollider.h"
#include "../Component/Physics/Collider/CircleCollider/CircleCollider.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"

SceneBase::SceneBase()
{
	world = new WorldMgr;
}


SceneBase::~SceneBase()
{
}

HRESULT SceneBase::Init(void)
{
	_IMAGE->CreateImage("Test", "Resource/Image/Test.png", { 2,1 });

	//GameObject* cam = new MainCamera(world);
	GameObject* test1 = new TestObject(world, { 400, 300 }, { 30, 30 }, PIVOT_LC);
	GameObject* test2 = new TestObject(world, { 0, 100 }, { 30,30 }, PIVOT_CC);

	world->Init();
	world->SetCurrentCam(test1);
	reinterpret_cast<TestObject*>(test1)->SetIsControll(true);

	return S_OK;
}

void SceneBase::Release(void)
{
	SafeRelease(world);
}

void SceneBase::Update(void)
{
	world->Update();
}

void SceneBase::Render(void)
{
	world->Render();
}
