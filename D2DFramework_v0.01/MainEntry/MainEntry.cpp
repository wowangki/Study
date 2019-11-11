#include "stdafx.h"
#include "MainEntry.h"

MainEntry::MainEntry()
{
}


MainEntry::~MainEntry()
{
	_BRUSH->ReleaseSingleton();
	_FONT->ReleaseSingleton();
	_KEY->ReleaseSingleton();
	_CAMERA->ReleaseSingleton();
	_IMAGE->ReleaseSingleton();
	_SOUND->ReleaseSingleton();
	_EFFECT->ReleaseSingleton();
	_SCENE->ReleaseSingleton();
}

HRESULT MainEntry::Init(void)
{

	return S_OK;
}

void MainEntry::Release(void)
{

}

void MainEntry::Update(void)
{
}

void MainEntry::Render(void)
{
	
}
