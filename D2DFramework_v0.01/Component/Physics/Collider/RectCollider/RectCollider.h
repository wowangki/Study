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
	D2D_RECT_F collBox;

public:
	RectCollider();
	explicit RectCollider(GameObject* object);
	virtual ~RectCollider();

	virtual HRESULT Init(D2D_POINT_2F pos = { 0.0f,0.0f }, D2D_SIZE_F size = { 0.0f,0.0f }, PIVOT pivot = PIVOT_CC, float angle = 0.0f) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
	
	virtual void IsCollision(Collider* col);
	virtual void IsCollision(void) {}

	inline D2D_RECT_F GetCollBox(void) const { return collBox; }

	
};

