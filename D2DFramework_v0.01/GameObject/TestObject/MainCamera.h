#pragma once
#include "../GameObject/GameObject.h"

class MainCamera : public GameObject
{
public:
	explicit MainCamera(WorldMgr * world);
	virtual ~MainCamera();

	// GameObject을(를) 통해 상속됨
	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
	virtual void OnCollisionEnter(Collider * coll) override {}
	virtual void OnCollisionStay(Collider * coll) override {}
	virtual void OnCollisionEnd(Collider * coll) override {}
	virtual void OnTriggerEnter(Collider * coll) override {}
	virtual void OnTriggerStay(Collider * coll) override {}
	virtual void OnTriggerEnd(Collider * coll) override {}
};

