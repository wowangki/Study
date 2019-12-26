#pragma once
#include "../System/Application/cApplication.h"
#include <vector>

class GameObject;
class MainEntry : public cApplication
{
private:

public:
	MainEntry();
	~MainEntry();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

