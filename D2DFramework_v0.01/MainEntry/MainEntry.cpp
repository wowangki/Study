#include "stdafx.h"
#include "MainEntry.h"
#include "../GameObject/Test/Test.h"
#include "../Module/Collider/CollMediator/CollisionMediator.h"
MainEntry::MainEntry()
{
}


MainEntry::~MainEntry()
{
	_COLOR->ReleaseSingleton();
	_FONT->ReleaseSingleton();
	_KEY->ReleaseSingleton();
	_CAMERA->ReleaseSingleton();
	_IMAGE->ReleaseSingleton();
	_SOUND->ReleaseSingleton();
	_SCENE->ReleaseSingleton();
}

HRESULT MainEntry::Init(void)
{
	mediator = new CollisionMediator();
	test = new Test({ WINSIZEX * 0.5f, WINSIZEY * 0.5f }, { 100,100 }, true, mediator);
	test2 = new Test({ WINSIZEX * 0.5f - 20, WINSIZEY * 0.5f - 20 }, { 100,100 }, false, mediator);

	return S_OK;
}

void MainEntry::Release(void)
{

}

void MainEntry::Update(void)
{
	test->Update();
	test2->Update();

	mediator->Update();
}

void MainEntry::Render(void)
{
	test->Render();
	test2->Render();
}
