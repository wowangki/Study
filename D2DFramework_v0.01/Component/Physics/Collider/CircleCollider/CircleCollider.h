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
	D2D1_ELLIPSE collBox;		//COLLBOX

public:
	CircleCollider();
	explicit CircleCollider(GameObject* object);
	virtual ~CircleCollider();

	virtual HRESULT Init(D2D_POINT_2F pos = { 0.0f,0.0f }, D2D_SIZE_F size = { 0.0f,0.0f }, PIVOT pivot = PIVOT_CC, float angle = 0.0f) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void IsCollision(Collider* col) override;
	virtual void IsCollision(void) {}

	inline D2D1_ELLIPSE GetCollBox(void) const { return collBox; }
	
};

