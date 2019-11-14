#pragma once
#include "../System/Application/cApplication.h"

class GameObject;
class CollisionMediator;
class MainEntry : public cApplication
{
private:
	GameObject* test;
	GameObject* test2;

	CollisionMediator* mediator;

public:
	MainEntry();
	~MainEntry();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

