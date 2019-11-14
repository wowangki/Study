#pragma once
#include "../GameObject.h"

class CollisionMediator;
class Test : public GameObject
{
private:
	bool isControl;

public:
	Test();
	explicit Test(D2D_POINT_2F pos, D2D_SIZE_F size, bool isControl, CollisionMediator* mediator);
	~Test();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
	virtual void SelectObject(void) {}
	virtual void SetObject(void) {}


	virtual void OnCollisionEnter(ColliderBase * other) override;
	virtual void OnCollisionStay(ColliderBase * other) override;
	virtual void OnCollisionExit(ColliderBase * other) {}
};

