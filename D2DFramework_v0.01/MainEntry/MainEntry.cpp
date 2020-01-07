#include "stdafx.h"
#include "MainEntry.h"
#include "SceneBase/SceneBase.h"

MainEntry::MainEntry()
{
}


MainEntry::~MainEntry()
{
	_BRUSH->ReleaseSingleton();
	_FONT->ReleaseSingleton();
	_KEYCODE->ReleaseSingleton();
	_IMAGE->ReleaseSingleton();
	_SOUND->ReleaseSingleton();
	_SCENE->ReleaseSingleton();
}

HRESULT MainEntry::Init(void)
{
	scene = new SceneBase;

	scene->Init();

	return S_OK;
}

void MainEntry::Release(void)
{
	SafeRelease(scene);
}

void MainEntry::Update(void)
{
	scene->Update();
}

void MainEntry::Render(void)
{
	scene->Render();
}
