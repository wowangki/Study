//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== COLLIDER BASE =========================//

#pragma once
#include "../Component.h"

class Transform;
class Collider : public Component {
protected:
	Transform* transform;			//TRANSFORM
	bool isColl;					//ISCOLLISION

public:

	virtual HRESULT Init(void)		= 0;
	virtual void Release(void)	= 0;
	virtual void Update(void)	= 0;
	virtual void Render(void)	= 0;

	virtual void IsCollision(Collider* col) = 0;
	virtual void IsCollision(void) = 0;

	inline Transform* GetTransform(void) const	{ return transform; }
	inline bool GetIsCollision(void) const		{ return isColl; }

	//Normal Set
	void SetTransform(Transform* transform)		{ this->transform = transform; }
	void SetIsCollision(bool isColl)			{ this->isColl = isColl; }

	//Channing Set
	Collider* SetTransformChain(Transform* transform) { 
		this->transform = transform; 
		return this;
	}

	Collider* SetIsCollisionChain(bool isColl){
		this->isColl = isColl; 
		return this;
	}

};