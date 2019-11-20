//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== CIRCLE COLLIDER =======================//

#pragma once
#include "../Collider.h"

class ICollision;
class CircleCollider final : public Collider
{
private:
	ICollision* myObject;		//COLLISION INTERFACE
	D2D1_ELLIPSE figure;		//FIGURE

public:
	CircleCollider();
	explicit CircleCollider(ICollision* myObject);
	~CircleCollider();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void IsCollision(Collider* col) override;

	inline D2D1_ELLIPSE GetFigure(void) const { return figure; }
};

