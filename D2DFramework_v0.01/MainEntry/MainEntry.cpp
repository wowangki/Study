#include "stdafx.h"
#include "MainEntry.h"
#include "../GameObject/TestObject/TestObject.h"
#include "../Component/Physics/Collider/RectCollider/RectCollider.h"
#include "../Component/Physics/Collider/CircleCollider/CircleCollider.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"

MainEntry::MainEntry()
{
}


MainEntry::~MainEntry()
{
	_BRUSH->ReleaseSingleton();
	_FONT->ReleaseSingleton();
	_KEYCODE->ReleaseSingleton();
	_OBJMGR->ReleaseSingleton();
}

HRESULT MainEntry::Init(void)
{
	_IMAGE->CreateImage("Test", "Resource/Image/Test.png", { 2,1 });

	_OBJMGR->Init();

	return S_OK;
}

void MainEntry::Release(void)
{
	_OBJMGR->Release();
	_COLLMGR->Release();
}

void MainEntry::Update(void)
{
	_OBJMGR->Update();
	_COLLMGR->Update();
}

void MainEntry::Render(void)
{
	_OBJMGR->Render();
}
