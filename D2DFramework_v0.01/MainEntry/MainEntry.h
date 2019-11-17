#pragma once
#include "../System/Application/cApplication.h"


class MainEntry : public cApplication
{

public:
	MainEntry();
	~MainEntry();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

