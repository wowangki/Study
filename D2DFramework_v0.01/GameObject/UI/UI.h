#pragma once
#include "../GameObject.h"
class UI : public GameObject
{
public:
	UI();
	~UI();

	// GameObject을(를) 통해 상속됨
	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
};

