//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== COLLIDER BASE =========================//

//====================== 2019.11.29 ========================//
//====================== 1Â÷ ¼öÁ¤  =========================//

#pragma once
#include "../Component/Component.h"

class Transform;
class Collider : public Component {
protected:
	Transform* transform;			//TRANSFORM
	bool isTrigger;					//ISTRIGGER
	bool isColl;					//ISCOLLISION

public:
	virtual HRESULT Init(D2D_POINT_2F pos = { 0.0f,0.0f }, D2D_SIZE_F size = { 0.0f,0.0f }, PIVOT pivot = PIVOT_CC, float angle = 0.0f) = 0;
	virtual void Release(void)	= 0;
	virtual void Update(void)	= 0;
	virtual void Render(void)	= 0;

	virtual void IsCollision(Collider* col) = 0;
	virtual void IsCollision(void) = 0;

	inline Transform* GetTransform(void) const	{ return transform; }
	inline bool GetIsCollision(void) const		{ return isColl; }
	inline bool GetIsTrigger(void) const		{ return isTrigger; }

	//Normal Set
	void SetTransform(Transform* transform)		{ this->transform = transform; }
	void SetIsTrigger(bool isTrigger)			{ this->isTrigger = isTrigger; }
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

	Collider* SetIsTriggerChain(bool isTrigger) { 
		this->isTrigger = isTrigger;
		return this;
	}

};