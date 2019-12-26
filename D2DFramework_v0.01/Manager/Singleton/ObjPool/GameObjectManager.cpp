#include "stdafx.h"
#include "GameObjectManager.h"
#include "../GameObject/GameObject.h"

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

HRESULT GameObjectManager::Init(void)
{
	for (UINT i = 0; i < vObjList.size(); i++)
	{
		vObjList[i]->Init();
	}

	return S_OK;
}

void GameObjectManager::Release(void)
{
	for (UINT i = 0; i < vObjList.size(); i++)
	{
		SafeRelease(vObjList[i]);
	}

	vObjList.clear();

	vector<GameObject*> vTemp;
	vTemp.swap(vObjList);
}

void GameObjectManager::Update(void)
{
	for (UINT i = 0; i < vObjList.size(); i++)
	{
		vObjList[i]->Update();
	}
}

void GameObjectManager::Render(void)
{
	for (UINT i = 0; i < vObjList.size(); i++)
	{
		vObjList[i]->Render();
	}
}
