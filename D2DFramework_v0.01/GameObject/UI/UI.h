#pragma once
#include "../GameObject.h"
class UI : public GameObject
{
public:
	UI();
	~UI();

	// GameObject��(��) ���� ��ӵ�
	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
};

