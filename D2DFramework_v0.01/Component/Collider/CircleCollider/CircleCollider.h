#pragma once
#include "../Collider.h"

class CircleCollider final : public Collider
{
private:
	D2D1_ELLIPSE figure;

public:
	CircleCollider();
	explicit CircleCollider(Transform* transform, PIVOT pivot = PIVOT_LT, bool isColl = false);
	explicit CircleCollider(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT_LT, bool isColl = false);
	~CircleCollider();

	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void IsCollision(Collider* col) override;

	inline D2D1_ELLIPSE GetFigure(void) const { return figure; }
};

