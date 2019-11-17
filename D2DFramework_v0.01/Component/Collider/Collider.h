#pragma once
#include "../Component.h"

class Transform;
class Collider : public Component {
protected:
	Transform* transform;
	PIVOT pivot;
	bool isColl;

public:

	virtual void Init(void)		= 0;
	virtual void Release(void)	= 0;
	virtual void Update(void)	= 0;
	virtual void Render(void)	= 0;

	virtual void IsCollision(Collider* col) = 0;

	inline Transform* GetTransform(void) const	{ return transform; }
	inline PIVOT GetPivot(void) const			{ return pivot; }
	inline bool GetIsCollision(void) const		{ return isColl; }

	void SetPivot(PIVOT pivot)					{ this->pivot = pivot; }
	void SetIsCollision(bool isColl)			{ this->isColl = isColl; }

};