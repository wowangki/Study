//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== RECT COLLIDER =========================//

//====================== 2019.11.29 ========================//
//====================== 1Â÷ ¼öÁ¤  =========================//

#pragma once
#include "../Collider.h"

class RectCollider final : public Collider
{
private:
	DEFINE_COMPONENT(RectCollider, Collider, false);

public:
	explicit RectCollider(GameObject* object);
	virtual ~RectCollider();

	virtual HRESULT Init(void) override;
	virtual HRESULT Init(D2D_POINT_2F pos, D2D_SIZE_F size, float angle = 0.0f) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	
	virtual void IsCollision(Collider* other) override;
	virtual void IsCollision(void) override {}	
};