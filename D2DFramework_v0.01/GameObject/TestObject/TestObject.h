#pragma once
#include "../GameObject.h"

class TestObject : public GameObject
{
private:
	float speed;
	bool isControll;


public:
	TestObject();
	explicit TestObject(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT_LT, float angle = 0.0f);
	~TestObject();

	// GameObject을(를) 통해 상속됨
	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	// GameObject을(를) 통해 상속됨
	virtual void OnCollisionEnter(Collider * coll) override;
	virtual void OnCollisionStay(Collider * coll) override;
	virtual void OnCollisionEnd(Collider * coll) override;
	virtual void OnTriggerEnter(Collider * coll) override;
	virtual void OnTriggerStay(Collider * coll) override;
	virtual void OnTriggerEnd(Collider * coll) override;

	void SetIsControll(bool isControll) { this->isControll = isControll; }
};

