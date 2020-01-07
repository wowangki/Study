//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== CIRCLE COLLIDER =======================//

//====================== 2019.11.29 ========================//
//====================== 1Â÷ ¼öÁ¤  =========================//

#pragma once
#include "../Collider.h"

class CircleCollider final : public Collider
{
private:
	DEFINE_COMPONENT(CircleCollider, Collider, false);

public:
	explicit CircleCollider(GameObject* object);
	virtual ~CircleCollider();

	virtual HRESULT Init(void) override;
	virtual HRESULT Init(D2D_POINT_2F pos, D2D_SIZE_F size, float angle = 0.0f) override;
	virtual void Release(void) override;
	virtual void Update(void) override;

	virtual void IsCollision(Collider* other) override;
	virtual void IsCollision(void) {}
};