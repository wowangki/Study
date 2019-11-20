//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== RECT COLLIDER =========================//

#pragma once
#include "../Collider.h"

class ICollision;
class RectCollider final : public Collider
{
private:
	ICollision* myObject;		//COLLISION INTERFACE
	D2D_RECT_F figure;			//FIGURE

public:
	RectCollider();
	explicit RectCollider(ICollision* myObject);
	~RectCollider();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
	
	virtual void IsCollision(Collider* col);

	inline D2D_RECT_F GetFigure(void) const { return figure; }
};

