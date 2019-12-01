#pragma once
#include "../System/Application/cApplication.h"

class GameObject;
class MainEntry : public cApplication
{
private:
	GameObject* t1;
	GameObject* t2;

public:
	MainEntry();
	~MainEntry();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

