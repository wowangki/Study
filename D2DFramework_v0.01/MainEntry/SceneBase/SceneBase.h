#pragma once
#include "Application/cApplication.h"

class SceneBase : public cApplication
{
private:
	class WorldMgr* world;

public:
	SceneBase();
	~SceneBase();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
};

