#pragma once
#include "../Component/Component.h"

class Camera : public Component
{


public:
	Camera();
	~Camera();

	// Component을(를) 통해 상속됨
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
};

