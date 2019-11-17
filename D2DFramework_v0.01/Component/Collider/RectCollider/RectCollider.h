#pragma once
#include "../Collider.h"

class RectCollider final : public Collider
{
private:
	D2D_RECT_F figure;

public:
	RectCollider();
	explicit RectCollider(Transform* transform, PIVOT pivot = PIVOT_LT, bool isColl = false);
	explicit RectCollider(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT_LT, bool isColl = false);
	~RectCollider();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
	
	virtual void IsCollision(Collider* col);

	inline D2D_RECT_F GetFigure(void) const { return figure; }
};

