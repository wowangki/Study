#pragma once
#include "../SingletonBase.h"

class KeyModule :public SingletonBase<KeyModule>
{
private:
	byte bKeyDown[256];
	byte prevKey;

public:
	KeyModule();
	~KeyModule();

	bool IsKeyDown(int keyCode);
	bool StayKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	bool ToggleKeyDown(int keyCode);
};

