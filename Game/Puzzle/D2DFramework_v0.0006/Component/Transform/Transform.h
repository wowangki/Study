//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== TRANSFORM  ============================//

#pragma once
#include "../Component.h"

class GameObject;
class Transform : public Component
{
private:
	GameObject* myObject;	// MyObject
	D2D_POINT_2F pos;		// POSITION
	D2D_SIZE_F size;		// SIZE
	D2D_RECT_F rc;			// RECT
	float angle;			// ANGLE of Radian
	PIVOT pivot;			//PIVOT

public:
	Transform();
	explicit Transform(GameObject* myObject);
	explicit Transform(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT_LT, float angle = 0.0f);
	virtual ~Transform();

	// Component을(를) 통해 상속됨
	virtual HRESULT Init(void)	override { return S_OK; }
	virtual void Release(void)	override {}
	virtual void Update(void)	override {}
	virtual void Render(void)	override {}

	void Translate(const D2D_POINT_2F power) {
		pos.x += power.x;
		pos.y += power.y;
	}

	inline D2D_POINT_2F GetPos(void)	const { return pos; }
	inline D2D_SIZE_F GetSize(void)		const { return size; }
	inline D2D_RECT_F GetRect(void)		const { return rc; }
	inline float GetAngle(void)			const { return angle; }
	inline PIVOT GetPivot(void)			const { return pivot; }

	// Normal Set
	void SetPos(D2D_POINT_2F pos)					{ this->pos = pos; }
	void SetPos(float x = 0, float y = 0)			{ pos.x = x; pos.y = y; }
	void SetSize(D2D_SIZE_F size)					{ this->size = size; }
	void SetSize(float width = 0, float height = 0) { size.width = width; size.height = height; }
	void SetRect(D2D_RECT_F rc)						{ this->rc = rc; }
	void SetAngleD(float degree)					{ this->angle = DegreeToRadian(degree); }
	void SetAngleR(float radian)					{ this->angle = radian; }
	void SetPivot(PIVOT pivot)						{ this->pivot = pivot; }

	//Chainning Set
	Transform* SetPosChain(D2D_POINT_2F pos) { 
		this->pos = pos; 
		return this;
	}

	Transform* SetPosChain(float x = 0, float y = 0) { 
		pos.x = x; pos.y = y; 
		return this;
	}

	Transform* SetSizeChain(D2D_SIZE_F size) { 
		this->size = size; 
		return this;
	}

	Transform* SetSizeChain(float width = 0, float height = 0) { 
		size.width = width; size.height = height; 
		return this;
	}

	Transform* SetAngleDChain(float degree) { 
		this->angle = DegreeToRadian(degree); 
		return this;
	}

	Transform* SetAngleRChain(float radian) { 
		this->angle = radian;
		return this;
	}

	Transform* SetPivotChain(PIVOT pivot) { 
		this->pivot = pivot; 
		return this;
	}
};

