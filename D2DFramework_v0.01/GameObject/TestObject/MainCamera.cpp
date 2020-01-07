#include "stdafx.h"
#include "MainCamera.h"
#include "../Manager/World/WorldMgr.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Graphic/Camera/Camera.h"

MainCamera::MainCamera(WorldMgr * world)
{
	this->world = world;
	this->world->RegistObjList(this);
	isActive = true;
	layer = LAYER::DEFAULT;

	AddComponent(new Transform(this))->Init({ WINSIZEX * 0.5f, WINSIZEY * 0.5f }, { 0,0 });
}

MainCamera::~MainCamera()
{
}

HRESULT MainCamera::Init(void)
{
	AddComponent(new Camera(this))->Init({ 100,100 });
	return S_OK;
}

void MainCamera::Release(void)
{
	mIter iter = mComponent.begin();
	for (iter; iter != mComponent.end(); ++iter) {
		SafeRelease(iter->second);
	}
	mComponent.clear();
}

void MainCamera::Update(void)
{
	mIter iter = mComponent.begin();
	for (iter; iter != mComponent.end(); ++iter) {
		iter->second->Update();
	}
}

void MainCamera::Render(void)
{
	mIter iter = mComponent.begin();
	for (iter; iter != mComponent.end(); ++iter) {
		iter->second->Render();
	}
}