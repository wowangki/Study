#include "stdafx.h"
#include "MainEntry.h"
#include "../GameObject/Map/Map.h"

MainEntry::MainEntry()
{
}


MainEntry::~MainEntry()
{
	_BRUSH->ReleaseSingleton();
	_FONT->ReleaseSingleton();
	_KEYCODE->ReleaseSingleton();
}

HRESULT MainEntry::Init(void)
{
	map = new Map({ 30,30 }, { 5,5 });

	map->Init();

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
	map->Render();
}
