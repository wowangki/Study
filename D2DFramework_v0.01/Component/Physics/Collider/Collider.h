//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== COLLIDER BASE =========================//

//====================== 2019.11.29 ========================//
//====================== 1Â÷ ¼öÁ¤  =========================//

#pragma once
#include "../Component/Component.h"
#include <vector>

class Transform;
class Collider : public Component {
private:
	DEFINE_COMPONENT(Collider, Component, true);

protected:
	Transform* transform;			//TRANSFORM
	bool isTrigger;					//ISTRIGGER
	bool isColl;					//ISCOLLISION

	struct CollBox {
		D2D_RECT_F* rc;
		D2D1_ELLIPSE* cir;
	} collBox;

public:
	
	virtual HRESULT Init(void) = 0;
	virtual HRESULT Init(D2D_POINT_2F pos, D2D_SIZE_F size, float angle = 0.0f) = 0;
	virtual void Release(void)	= 0;
	virtual void Update(void)	= 0;
	virtual void Render(void) {};

	virtual void IsCollision(Collider* other) = 0;
	virtual void IsCollision(void) = 0;

	inline CollBox GetCollBox(void) const		{ return collBox; }
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