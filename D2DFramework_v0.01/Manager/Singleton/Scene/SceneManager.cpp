#include "stdafx.h"
#include "SceneManager.h"

cApplication* SceneManager::currentScene = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	mIter iter = mScene.begin();

	for (iter; iter != mScene.end(); ++iter) {
		SafeDeleteClass(iter->second);
	}

}

void SceneManager::Update(void)
{
	if (currentScene)
		currentScene->Update();
}

void SceneManager::Render(void)
{
	if (currentScene)
		currentScene->Render();
}

cApplication * SceneManager::CreateScene(string sceneName, cApplication * curScene)
{
	if (!curScene) return nullptr;

	mScene.insert(make_pair(sceneName, curScene));

	return curScene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	mIter iter = mScene.find(sceneName);

	if (iter == mScene.end()) return E_FAIL;
	if (iter->second == currentScene) return S_OK;

	if (SUCCEEDED(iter->second->Init())) {
		if (currentScene) currentScene->Release();

		currentScene = iter->second;
		return S_OK;
	}

	return E_FAIL;
}
