#pragma once
#include "../Module/Collider/ColliderBase.h"

class RectCollider final : public ColliderBase
{
private: 
	D2D_RECT_F collider;

public:
	RectCollider();
	explicit RectCollider(GameObject* object, Transform* transform, 
		PIVOT pivot = PIVOT_LT, bool onTrigger = false, 
		CollisionMediator* mediator = nullptr);

	~RectCollider();

	virtual void Update(ColliderBase* coll) override;
	virtual void Render(void) override;

	inline D2D_RECT_F GetCollider(void) const { return collider; }

};

