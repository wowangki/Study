#pragma once
#include "../Utill/CollisionHelper.h"

class GameObject;
class Transform;
class CollisionMediator;
class ColliderBase
{
protected:
	GameObject* object;				// This Having Object;
	Transform* transform;			// Transform;
	PIVOT pivot;					// pivot
	bool onTrigger;					// OnTrigger
	bool isCollision;				// ChkCollision


public: 
	virtual void Update(ColliderBase* coll) = 0;
	virtual void Render(void) = 0;

public:
	// Getter & Setter
	inline GameObject* GetGameObject(void) const { return object; }
	inline Transform* GetTransform(void) const { return transform; }
	inline PIVOT GetPivot(void) const { return pivot; }
	inline bool GetOnTrigger(void) const { return onTrigger; }

	void SetTransform(Transform* transform) { this->transform = transform; }
	void SetPivot(PIVOT pivot) { this->pivot = pivot; }
	void SetOnTrigger(bool onTrigger) { this->onTrigger = onTrigger; }

};

