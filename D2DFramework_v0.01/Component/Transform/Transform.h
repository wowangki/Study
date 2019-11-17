#pragma once
#include "../Component.h"

class Transform : public Component
{
private:
	D2D_POINT_2F pos;	// POSITION
	D2D_SIZE_F size;	// SIZE
	float angle;		// ANGLE of Radian

public:
	Transform();
	explicit Transform(D2D_POINT_2F pos, D2D_SIZE_F size, float angle = 0.0f);
	~Transform();

	// Component을(를) 통해 상속됨
	virtual void Init(void)		override {};
	virtual void Release(void)	override {};
	virtual void Update(void)	override {};
	virtual void Render(void)	override {};

	inline D2D_POINT_2F GetPos(void)	const { return pos; }
	inline D2D_SIZE_F GetSize(void)		const { return size; }
	inline float GetAngle(void)			const { return angle; }

	void SetPos(D2D_POINT_2F pos)					{ this->pos = pos; }
	void SetPos(float x = 0, float y = 0)			{ pos.x = x; pos.y = y; }
	void SetSize(D2D_SIZE_F size)					{ this->size = size; }
	void SetSize(float width = 0, float height = 0) { size.width = width; size.height = height; }
	void SetAngleD(float degree)					{ this->angle = DegreeToRadian(degree); }
	void SetAngleR(float radian)					{ this->angle = radian; }
};

