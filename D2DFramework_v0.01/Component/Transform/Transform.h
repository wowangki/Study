#pragma once

class Transform 
{
private:
	D2D_POINT_2F pos;		// POSITION
	D2D_SIZE_F size;		// SIZE
	float angle;			// ANGLE

public:
	Transform();
	~Transform();
	
	//Getter & Setter

	inline D2D_POINT_2F GetPos(void) const { return pos; }
	inline D2D_SIZE_F GetSize(void) const { return size; }
	inline float GetAngle(void) const { return angle; }

	inline float GetDistance(Transform* other) const {
		return sqrtf(pow(pos.x - other->GetPos().x, 2) + pow(pos.y - other->GetPos().y, 2));
	}

	void SetPos(D2D_POINT_2F pos) { this->pos = pos; }
	void SetPos(float x = 0, float y = 0) { 
		this->pos.x = x; 
		this->pos.y = y; 
	}

	void SetSize(D2D_SIZE_F size) { this->size = size; }
	void SetSize(float scaleX, float scaleY) { 
		this->size.width *= scaleX; 
		this->size.height *= scaleY; 
	}

	void SetDegree(float degree) { this->angle = DegreeToRadian(degree); }
	void SetAngle(float radian) { this->angle = radian; }

};

