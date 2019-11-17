#include "stdafx.h"
#include "MainEntry.h"

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
