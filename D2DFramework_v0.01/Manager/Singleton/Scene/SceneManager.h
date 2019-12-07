#pragma once
#include "../SingletonBase.h"
#include "../System/Application/cApplication.h"
#include <map>

class SceneManager :public SingletonBase<SceneManager>
{
private:
	typedef map<string, cApplication*> _mScene;
	typedef map<string, cApplication*>::iterator mIter;

	static cApplication* currentScene;

	_mScene mScene;

	DWORD loadingThreadID; //쓰레드 ID 값

public:
	SceneManager();
	~SceneManager();

	void Update(void);
	void Render(void);

public:
	cApplication* CreateScene(string sceneName, cApplication* curScene);
	HRESULT ChangeScene(string sceneName);
};

