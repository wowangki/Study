#pragma once
#include "../SingletonBase.h"

class CameraModule : public SingletonBase<CameraModule>
{
public:
	float x, y;

	CameraModule();
	~CameraModule();
};

