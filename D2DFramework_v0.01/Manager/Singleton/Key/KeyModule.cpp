#include "stdafx.h"
#include "KeyModule.h"


KeyModule::KeyModule()
	:prevKey(0)
{
	ZeroMemory(bKeyDown, sizeof bKeyDown);
}


KeyModule::~KeyModule()
{
}

bool KeyModule::IsKeyDown(int keyCode)
{
	if (GetAsyncKeyState(keyCode) & 0x8000) {
		if (!bKeyDown[keyCode]) {
			bKeyDown[keyCode] = 0x01;
			return true;
		}
	}
	else bKeyDown[keyCode] = 0;

	return false;
}

bool KeyModule::StayKeyDown(int keyCode)
{
	if (GetAsyncKeyState(keyCode) & 0x8000) {
		prevKey = keyCode;
		return true;
	}

	return false;
}

bool KeyModule::IsKeyUp(int keyCode)
{
	if (!StayKeyDown(keyCode)) {
		if (prevKey == keyCode) {
			prevKey = 0;
			return true;
		}
	}

	return false;
}

bool KeyModule::ToggleKeyDown(int keyCode)
{
	if (GetKeyState(keyCode) & 0x0001) return true;

	return false;
}
