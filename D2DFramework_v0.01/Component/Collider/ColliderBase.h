#pragma once
#include "../ComponentBase.h"
#include "CollisionHelper.h"

class Transform;
class ColliderBase : public ComponentBase
{
protected:
	Transform* transform;		// Transform

	ITrigger* Itrigger;			// TriggerInterface
	bool isColl;				// isCollision
	bool isTrigger;				// isTrigger
	

public:
	virtual void Update(void) = 0;

	inline bool GetIsColl(void) { return isColl; }
	inline bool GetIsTrigger(void) { return isTrigger; }

	void SetIsColl(bool isColl) { this->isColl = isColl; }
	void SetIsTrigger(bool isTrigger) { this->isTrigger = isTrigger; }
};

